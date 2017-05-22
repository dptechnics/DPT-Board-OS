/**
 * @file network.c
 * @author Daan Pape <daan@dptechnics.com>
 * @date 5 Nov 2014
 * @copyright DPTechnics
 * @brief DPT-connector IoT-connector network functions
 *
 * @section LICENSE
 *
 * Copyright (c) 2014, Daan Pape
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 *     1. Redistributions of source code must retain the above copyright 
 *        notice, this list of conditions and the following disclaimer.
 *
 *     2. Redistributions in binary form must reproduce the above copyright 
 *        notice, this list of conditions and the following disclaimer in the 
 *        documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @section DESCRIPTION
 *
 * This file contains all the network functions for the DPTechnics BlueCherry
 * Internet-of-Things connector.
 */

#include <stdbool.h>
#include <stddef.h>
#include <json-c/json.h>
#include <curl/curl.h>
#include <string.h>

#include "network.h"
#include "log.h"
#include "config.h"
#include "device.h"

/**
 * @defgroup _NETWORK All network related compiled-in configuration.
 * @{
 */

/**
 * @brief The URL to request an SSH node on.
 */
#define _NETWORK_URL_REQUEST_SSH_NODE               "/devapi/platformconnect"

/**
 * @brief The URL to check platform reachability on.
 */
#define _NETWORK_URL_CONN_DETECTION                 "/devapi/hello"

/**
 * @brief The URL to post a new public SSH key to.
 */
#define _NETWORK_URL_POST_SSH_KEY                   "/devapi/newkey"

/**
 * @brief The user agent to use when contacting the update services.
 */
#define _NETWORK_USER_AGENT                         "dpt-device/1.0 DPT-connector/1.0"

/**
 * @brief The default SSL/TLS version to uses when contacting the update services.
 */
#define _NETWORK_SSL_VERSION                        CURL_SSLVERSION_TLSv1_2

/** @}*/

/**
 * @brief This structure represents a non 0-terminated string for use in the 
 * CURL write callback functions.
 */
struct _chararray {
    char *array;        /**< The character array. */
    size_t len;         /**< The number characters in the array, not counting the 0-terminator. */
};

/**
 * @brief Initialize a character array.
 * 
 * This function initializes the character array by reserving 1 byte and setting
 * it to 0. 
 *  
 * @param arr The character array to initialize.
 * 
 * @return True on success. 
 */
static bool _chararray_init(struct _chararray *arr)
{
    arr->len = 0;
    arr->array = (char*) calloc(1, sizeof(char));
    
    return arr->array != NULL;
}

/**
 * @brief Free a character array if it was reserved.
 * 
 * This function will free a character array if the internal pointer is not
 * NULL.
 * 
 * @param arr The character array to free.
 */
static void _chararray_free(struct _chararray *arr)
{
    arr->len = 0;
    
    if(arr->array != NULL) {
        free(arr->array);
    }
    arr->array = NULL;
}

/**
 * @brief Function called by CURL when a new chunk of response data is available.
 * 
 * This function will be called by CURL on every chunk of response data it
 * receives. When necessary the function will expand the string space reserved
 * in memory while it copies in the received data.  
* 
 * @param contents The contents of the the chunk of data received by CURL.
 * @param size The size, in bytes, of a member in the @ref contents array.
 * @param nmemb The number of members in the @ref contents array.
 * @param arr The character array to write the chunk in.
 * 
 * @return The number of bytes which were processed.
 */
static size_t _curl_write_callback(void *contents, size_t size, size_t nmemb, struct _chararray *arr)
{
    /* Calculate the chunk size */
    size_t chunk_size = size * nmemb;
    
    /* Expand the character array to contain the current length, 0-terminator and new chunk */
    arr->array = (char*) realloc(arr->array, arr->len + 1 + chunk_size);
    if(arr->array == NULL) {
        log_event(LG_ERROR, "CURL could not write new chunk, out of memory\n");
        return 0;
    }
    
    /* Copy in the new data */
    memcpy(arr->array + arr->len, contents, chunk_size);
    arr->len += chunk_size;
    
    /* 0-terminate the response */
    arr->array[arr->len] = '\0';
    
    return chunk_size;
}

/**
 * @brief General CURL object request initialization. 
 * 
 * This function initializes the CURL object and applies the generic settings
 * to perform a secure request.
 * 
 * @param curl The CURl object to set-up.
 * @param url The URL to do the request on.
 * @param errorbuffer The buffer for CURL to write it's error in.
 * 
 * @return True on success. 
 */
static bool _curl_easy_prepare(CURL *curl, char *url, char* errorbuffer)
{
    /* Set up the URL */
    if(curl_easy_setopt(curl, CURLOPT_URL, url) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_URL could not be set to '%s'\n", url);
        return false;
    }
    
    /* Make sure strict name check for SSL is enabled */
    if(curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_SSL_VERIFYHOST could not be set to 2\n");
        return false;
    }
    
    /* Make sure strict name check for SSL is enabled */
    if(curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_SSL_VERIFYHOST could not be set to 2\n");
        return false;
    }
    
    /* Make sure strict certificate check for SSL is enabled */
    if(curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_SSL_VERIFYPEER could not be set to 1\n");
        return false;
    }
    
    /* Set the SSL version to use with the server */
    if(curl_easy_setopt(curl, CURLOPT_SSLVERSION, _NETWORK_SSL_VERSION) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_SSLVERSION could not be set.\n");
        return false;
    }
    
    /* Set up the user agent */
    if(curl_easy_setopt(curl, CURLOPT_USERAGENT, _NETWORK_USER_AGENT) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_USERAGENT could not be set.\n");
        return false;
    }
    
    /* Set up the CURL error buffer */
    if(curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorbuffer) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_ERRORBUFFER could not be set.\n");
        return false;
    }
    
    return true;
}

/**
 * @brief This function requests an SSH endpoint to the BlueCherry platform.
 * 
 * This function will connect to the BlueCherry IoT platform and request 
 * an SSH node to connect to.
 * 
 * @param serv The @c ssh_server structure to write the connection info in.
 * 
 * @return true on success, false on error. 
 */
bool network_request_ssh_server(struct ssh_server *serv)
{
    bool retvalue = true;
    
    /* Read the type ID from flash */
    char dev_type_id[DEVICE_TYPE_ID_BUFF_LEN];
    if(!device_get_type_id(dev_type_id)) {
        log_event(LG_ERROR, "Could not read device type ID from flash\n");
        return false;
    }
    
    /* Read the device ID from flash */
    char dev_dev_id[DEVICE_ID_BUFF_LEN];
    if(!device_get_device_id(dev_dev_id)) {
        log_event(LG_ERROR, "Could not read device ID from flash\n");
        return false;
    }
    
    /* Read the device key from flash */
    char dev_dev_key[DEVICE_DEVICE_KEY_BUFF_LEN];
    if(!device_get_device_key(dev_dev_key)) {
        log_event(LG_ERROR, "Could not read device key from flash\n");
        return false;
    }
    
    /* Construct the request JSON message */
    json_object *json_request = json_object_new_object();
    json_object_object_add(json_request, "type_id", json_object_new_string(dev_type_id));
    json_object_object_add(json_request, "device_id", json_object_new_string(dev_dev_id));
    json_object_object_add(json_request, "device_key", json_object_new_string(dev_dev_key));
    const char *request = json_object_to_json_string(json_request);
    
    /* Initialize the CURL library */
    CURL *curl = curl_easy_init();
    if(!curl) {
        log_event(LG_ERROR, "The CURL library could not be initialized\n");
        json_object_put(json_request);
        return false;
    }
    
    /* Allocate response and error buffers */
    char error_buffer[CURL_ERROR_SIZE] = { 0 };
    struct _chararray arr;
    if(!_chararray_init(&arr)) {
        log_event(LG_ERROR, "The response buffer could not be initialized\n");
        goto error;
    }
    
    /* Format the URL */
    char url[256];
    snprintf(url, 256, "https://%s%s", appconf->bluecherry_address, _NETWORK_URL_REQUEST_SSH_NODE);
       
    /* Prepare the request and apply the generic CURL settings */
    if(!_curl_easy_prepare(curl, url, error_buffer)) {
        goto error;
    }
    
    /* Set up the write function */
    if(curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _curl_write_callback) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_WRITEFUNCTION could not be set\n");
        goto error;
    }
    
    /* Set up the pointer to write the received data in */
    if(curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) &arr) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_WRITEFUNCTION could not be set\n");
        goto error;
    }
    
    /* Tell CURL this is a post request */
    if(curl_easy_setopt(curl, CURLOPT_POST, 1L) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_POST could not be set\n");
        goto error;
    }
    
    /* Set the POST data */
    if(curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_POSTFIELDS could not be set\n");
        goto error;
    }
    
    /* Perform the POST */
    CURLcode result = curl_easy_perform(curl);
    if(result != CURLE_OK) {
        log_event(LG_ERROR, "CURL could not POST SSH node request: (err: #%d) %s\n", result, error_buffer);
        goto error;
    }
    
    /* Make sure the response we got from the BlueCherry service is 200 OK  */
    long http_resp;
    curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &http_resp);
    if (http_resp != 200) {
        log_event(LG_ERROR, "The BlueCherry service responded with code %ld\n", http_resp);
        goto error;
    }
    
    /* Now parse the response */
    json_object *json_response = json_tokener_parse(arr.array);
    if(json_response == NULL) {
        log_event(LG_ERROR, "The BlueCherry service response could not be parsed\n");
        goto error;
    }
    
    /* Get the BlueCherry access result */
    json_object *j_has_access;
    if(!json_object_object_get_ex(json_response, "result", &j_has_access)) {
        log_event(LG_ERROR, "Could not parse boolean 'result' from BlueCherry service response\n");
        json_object_put(json_response);
        goto error;
    }
    
    /* Check if response was positive */
    if(!json_object_get_boolean(j_has_access)) {
        log_event(LG_WARNING, "This device doesn't have BlueCherry platform access\n");
        json_object_put(json_response);
        goto error;
    }
        
    /* Load values in the server structure */
    json_object *j_port;;
    json_object *j_ipv4;
    json_object *j_ipv6;
    json_object *j_serverport;
    json_object *j_hostkey; 
    if(!json_object_object_get_ex(json_response, "port", &j_port) ||
       !json_object_object_get_ex(json_response, "ipv4", &j_ipv4) ||
       !json_object_object_get_ex(json_response, "ipv6", &j_ipv6) ||
       !json_object_object_get_ex(json_response, "serverport", &j_serverport) ||
       !json_object_object_get_ex(json_response, "hostkey", &j_hostkey))
    {
        log_event(LG_ERROR, "The BlueCherry platform sent a malformed response\n");
        json_object_put(json_response);
        goto error;
    }
        
    serv->port = json_object_get_int(j_port);
    strncpy(serv->ipv4, json_object_get_string(j_ipv4), INET_ADDRSTRLEN);
    strncpy(serv->ipv6, json_object_get_string(j_ipv6), INET6_ADDRSTRLEN);
    serv->serverport = json_object_get_int(j_serverport);
    strncpy(serv->hostkey, json_object_get_string(j_hostkey), NETWORK_SERVER_HKEY_LEN);
        
cleanup:
    /* Free allocated memory and return true */
    json_object_put(json_request);
    curl_easy_cleanup(curl);
    _chararray_free(&arr);
    return retvalue;

error:
    retvalue = false;
    goto cleanup;
}

/**
 * @brief Check if the BlueCherry platform is reachable.
 * 
 * This function will try to connect to the BlueCherry platform @c hello link
 * to see if the platform is reachable.
 * 
 * @return True when the BlueCherry platform is reachable.
 */
bool network_check_bluecherry_conn()
{
    bool retvalue = true;
    
    /* Initialize the CURL library */
    CURL *curl = curl_easy_init();
    if(!curl) {
        log_event(LG_ERROR, "The CURL library could not be initialized\n");
        return false;
    }
    
    /* Allocate response and error buffers */
    char error_buffer[CURL_ERROR_SIZE] = { 0 };
    
    /* Format the URL */
    char url[256];
    snprintf(url, 256, "https://%s%s", appconf->bluecherry_address, _NETWORK_URL_CONN_DETECTION);
       
    /* Prepare the request and apply the generic CURL settings */
    if(!_curl_easy_prepare(curl, url, error_buffer)) {
        goto error;
    }
    
    /* Perform the GET request */
    CURLcode result = curl_easy_perform(curl);
    if(result != CURLE_OK) {
        log_event(LG_ERROR, "CURL could not not perform GET request to the BlueCherry platform: (err: #%d) %s\n", result, error_buffer);
        goto error;
    }
    
    /* Make sure the response we got from the BlueCherry service is 200 OK  */
    long http_resp;
    curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &http_resp);
    if (http_resp != 200) {
        log_event(LG_ERROR, "The BlueCherry service responded with code %ld\n", http_resp);
        goto error;
    }

cleanup:
    /* Free allocated memory and return true */
    curl_easy_cleanup(curl);
    return retvalue;

error:
    retvalue = false;
    goto cleanup;
}

/**
 * @brief This function uploads a new public key to the BlueCherry platform.
 * 
 * This function will try to upload a new public SSH key to the BlueCherry
 * Internet-of-Things platform. All data needed for uploading is read from
 * the device flash.
 * 
 * @return True when the key uploaded successfully.
 */
bool network_update_ssh_key()
{
    bool retvalue = true;
    
    /* Read the type ID from flash */
    char dev_type_id[DEVICE_TYPE_ID_BUFF_LEN];
    if(!device_get_type_id(dev_type_id)) {
        log_event(LG_ERROR, "Could not read device type ID from flash\n");
        return false;
    }
    
    /* Read the device ID from flash */
    char dev_dev_id[DEVICE_ID_BUFF_LEN];
    if(!device_get_device_id(dev_dev_id)) {
        log_event(LG_ERROR, "Could not read device ID from flash\n");
        return false;
    }
    
    /* Read the device key from flash */
    char dev_dev_key[DEVICE_DEVICE_KEY_BUFF_LEN];
    if(!device_get_device_key(dev_dev_key)) {
        log_event(LG_ERROR, "Could not read device key from flash\n");
        return false;
    }
    
    char ssh_pubkey[DEVICE_SSH_PUBLIC_KEY_BUFF_LEN];
    if(!device_get_ssh_public_key(ssh_pubkey)) {
        log_event(LG_ERROR, "Could not read public SSH key from flash\n");
        return false;
    }
    
    /* Construct the request JSON message */
    json_object *json_request = json_object_new_object();
    json_object_object_add(json_request, "type_id", json_object_new_string(dev_type_id));
    json_object_object_add(json_request, "device_id", json_object_new_string(dev_dev_id));
    json_object_object_add(json_request, "device_key", json_object_new_string(dev_dev_key));
    json_object_object_add(json_request, "ssh_key", json_object_new_string(ssh_pubkey));
    const char *request = json_object_to_json_string(json_request);
    
    /* Initialize the CURL library */
    CURL *curl = curl_easy_init();
    if(!curl) {
        log_event(LG_ERROR, "The CURL library could not be initialized\n");
        json_object_put(json_request);
        return false;
    }
    
    /* Allocate response and error buffers */
    char error_buffer[CURL_ERROR_SIZE] = { 0 };
    
    /* Format the URL */
    char url[256];
    snprintf(url, 256, "https://%s%s", appconf->bluecherry_address, _NETWORK_URL_POST_SSH_KEY);
       
    /* Prepare the request and apply the generic CURL settings */
    if(!_curl_easy_prepare(curl, url, error_buffer)) {
        goto error;
    }

    /* Tell CURL this is a post request */
    if(curl_easy_setopt(curl, CURLOPT_POST, 1L) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_POST could not be set\n");
        goto error;
    }
    
    /* Set the POST data */
    if(curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request) != CURLE_OK) {
        log_event(LG_ERROR, "Option CURLOPT_POSTFIELDS could not be set\n");
        goto error;
    }
    
    /* Perform the POST */
    CURLcode result = curl_easy_perform(curl);
    if(result != CURLE_OK) {
        log_event(LG_ERROR, "CURL could not POST SSH node request: (err: #%d) %s\n", result, error_buffer);
        goto error;
    }
    
    /* Make sure the response we got from the BlueCherry service is 201 Created  */
    long http_resp;
    curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &http_resp);
    if (http_resp != 201) {
        log_event(LG_ERROR, "The BlueCherry service responded with code %ld\n", http_resp);
        goto error;
    }
       
cleanup:
    /* Free allocated memory and return true */
    json_object_put(json_request);
    curl_easy_cleanup(curl);
    return retvalue;

error:
    retvalue = false;
    goto cleanup;    
}