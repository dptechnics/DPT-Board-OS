/* 
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
 * File:   dptnetwork.c
 * Created on November 5, 2014, 8:51 AM
 */

#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <syslog.h>
#include <json-c/json.h>
#include <curl/curl.h>
#include <stddef.h>
#include <netinet/in.h>

#include "dptnetwork.h"
#include "logger.h"
#include "config.h"

/**
 * Helper function for libcURL. 
 * @param contents the contents to write to the memory.
 * @param size the size of a memory member. 
 * @param nmemb the number of members.
 * @param userp the memory struct to write to.
 * @return 
 */
static size_t _write_mem_callback(void *contents, size_t size, size_t nmemb, void *userp) {
#ifdef DEBUG
    printf("Calling _write_mem_callback, buffer length: %d\r\n", (int) size);
#endif 
    size_t realsize = size * nmemb;
    struct curl_mem_struct *mem = (struct curl_mem_struct*) userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        syslog(LOG_ERR, "Not enough memory to save HTTP response");
#ifdef DEBUG
        printf("_write_mem_callback not enough memory to save HTTP response\r\n");
#endif 
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

/**
 * Request an SSH server node to connect to. 
 * @param serv structure to fill up on success. 
 * @return true on success, false on error. 
 */
bool dptnet_request_ssh_server(ssh_server* serv)
{
    CURL *curl; 
    CURLcode res;
    
    /* Create buffers */
    long http_resp; 
    bool retvalue = false; 
    char errbuff[CURL_ERROR_SIZE] = {0};
    char urlbuff[CONFIG_BUFF_SIZE];
    struct curl_mem_struct chunk;
    
    /* Allocate memory for response */
    chunk.memory = malloc(1);
    chunk.size = 0;
    
    /* Create JSON post data */
    json_object* jobj = json_object_new_object();
    json_object_object_add(jobj, "type_id", json_object_new_string(conf->typeid));
    json_object_object_add(jobj, "device_id", json_object_new_string(conf->devid));
    json_object_object_add(jobj, "device_key", json_object_new_string(conf->devkey));

    /* Initialize cURL */
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
#ifdef DEBUG
        printf("Succesfully initialized cURL to make SSH node request\r\n");
#endif
        /* Format url */
        snprintf(urlbuff, CONFIG_BUFF_SIZE - 1, "https://%s/devapi/platformconnect", conf->platform_url);
        
        /* Set correct post options */
        curl_easy_setopt(curl, CURLOPT_URL, urlbuff);
        curl_easy_setopt(curl, CURLOPT_CAINFO, conf->ssl_cert_path);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_object_to_json_string(jobj));
        
#ifdef NO_SSL_CHECK
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif  
        
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuff);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, CURL_USER_AGENT);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuff);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _write_mem_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

#ifdef DEBUG
        printf("Requesting %s to %s\r\n", json_object_to_json_string(jobj), urlbuff);
#endif
        
        /* Perfrom server request */
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            syslog(LOG_ERR, "Could not perform port request: (err: #%d) %s", res, errbuff);
#ifdef DEBUG
            printf("Could not perform port request: (err: #%d) %s\r\n", res, errbuff);
#endif
            goto end;
        }

        curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &http_resp);
        if(http_resp != 200) {
            syslog(LOG_ERR, "BlueCherry platform port request was no success, got %ld", http_resp);
#ifdef DEBUG
            printf("BlueCherry platform port request was no success, got %ld\r\n", http_resp);
#endif
            goto end;
        }

#ifdef DEBUG
            printf("Parsing incoming request %s\r\n", chunk.memory);
#endif
            
        /* Parse the answer */
        json_object *in_obj = json_tokener_parse(chunk.memory);
	json_object *j_result = NULL;
	if(!json_object_object_get_ex(in_obj, "result", &j_result)) {
	    /* There was an error on the platform side */
            syslog(LOG_WARNING, "DPT-Connector received negative response from DPT-Platform");
            json_object_put(in_obj);
            goto end;
	}
        
        /* Check if response was positive */
        if(!json_object_get_boolean(j_result)) {
            /* There was an error on the platform side */
            syslog(LOG_WARNING, "DPT-Connector received negative response from DPT-Platform");
            json_object_put(in_obj);
            goto end;
        }
        
        /* Load values in the server structure */
        json_object *j_port = NULL;
        json_object *j_ipv4 = NULL;
        json_object *j_ipv6 = NULL;
        json_object *j_serverport = NULL;
        json_object *j_hostkey = NULL;
        
        if(!json_object_object_get_ex(in_obj, "port", &j_port) ||
           !json_object_object_get_ex(in_obj, "ipv4", &j_ipv4) ||
           !json_object_object_get_ex(in_obj, "ipv6", &j_ipv6) ||
           !json_object_object_get_ex(in_obj, "serverport", &j_serverport) ||
           !json_object_object_get_ex(in_obj, "hostkey", &j_hostkey))
        {
            /* There was an error on the platform side */
            syslog(LOG_WARNING, "DPT-Connector received negative response from DPT-Platform");
            json_object_put(in_obj);
            goto end;
        }
        
        serv->port = json_object_get_int(j_port);
        strncpy(serv->ipv4, json_object_get_string(j_ipv4), INET_ADDRSTRLEN);
        strncpy(serv->ipv6, json_object_get_string(j_ipv6), INET6_ADDRSTRLEN);
        serv->serverport = json_object_get_int(j_serverport);
        strncpy(serv->hostkey, json_object_get_string(j_hostkey), DPTNET_SERVER_HKEY_LEN);
        
        /* It was a success */
        retvalue = true;
        
        /* Free response */
        json_object_put(in_obj);
        
end:
        /* Free chunk */
        free(chunk.memory);

        /* Cleanup cURL */
        curl_easy_cleanup(curl);
    }
    
    /* Clean up resources */
    curl_global_cleanup();
    json_object_put(jobj);
    
    return retvalue; 
}

/**
 * Returns true when the DPT-Connector can reach
 * the BlueCherry platform. 
 * @return true when the BlueCherry platform is reachable. 
 */
bool dptnet_check_bluecherry_conn()
{
    CURL *curl; 
    CURLcode res;
    
    /* Create buffers */
    long http_resp; 
    bool retvalue = false; 
    char errbuff[CURL_ERROR_SIZE] = {0};
    char urlbuff[CONFIG_BUFF_SIZE];

    /* Initialize cURL */
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        /* Format url */
        snprintf(urlbuff, CONFIG_BUFF_SIZE - 1, "https://%s/devapi/hello", conf->platform_url);
#ifdef DEBUG
        printf("Testing BlueCherry reachability on %s\r\n", urlbuff);
#endif
        
        /* Set correct post options */
        curl_easy_setopt(curl, CURLOPT_URL, urlbuff);
        curl_easy_setopt(curl, CURLOPT_CAINFO, conf->ssl_cert_path);
        
#ifdef NO_SSL_CHECK
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif  
        
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuff);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, CURL_USER_AGENT);

        /* Perform the hello check */
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
#ifdef DEBUG
        printf("Testing BlueCherry reachability got negative result: %d\r\n", res);
#endif
            goto end;
        }

        curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &http_resp);
#ifdef DEBUG
        printf("Testing BlueCherry reachability HTTP response code: %ld\r\n", http_resp);
#endif
        retvalue = http_resp == 200;

end:
        /* Cleanup cURL */
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return retvalue;
}
