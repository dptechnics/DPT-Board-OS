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
 * File:   config.c
 * Created on March 10, 2015, 6:28 PM
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <syslog.h>
#include <limits.h>

#include "config.h"
#include "logger.h"

/**
 * Trim leading and trailing whitespace from a function. Original
 * by Adam Rosenfield on http://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
 * @param str the string to trim.
 * @return the trimmed string. Do not call free on this one. 
 */
static char* trimwhitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace(*str)) str++;

    if (*str == 0)
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;

    // Write new null terminator
    *(end + 1) = 0;

    return str;
}

/**
 * Reserve memory and copy a string to it, be assured the string
 * is 0-terminated. 
 * @param destination the destination to copy to, if NULL new memory will be allocated. 
 * @param source the source string to copy. 
 * @return NULL on 
 */
static char* strmalloc(char* destination, const char* source) {
    size_t s_size = strlen(source);
    
    char* buff = (char*) realloc(destination, (s_size + 1) * sizeof(char));
    
    if(buff == NULL) {
        // Could not allocate memory, out of memory?
        syslog(LOG_ERR, "Could not allocate memory in config.c:63, out of memory?");
        return NULL;
    }
    
    memcpy(buff, source, s_size);
    
    // Make sure string is null terminated
    *(buff+s_size) = '\0';
    
    return buff;
}

/**
 * Parse an integer from a string on a safe way. 
 * @param string the string to parse to integer.
 * @param unsignedint if set to true, the fallback value will be used if the integer is negative.  
 * @param integer to fallback to if parsing fails.
 * @return the parsed integer on success, fallback on failure. 
 */
static int parseint(char* string, bool unsignedint, int fallback) {
    errno = 0;
    char* end = string;
    long result =  strtol(string, &end, 10);   
    
    if (errno == ERANGE) {
        syslog(LOG_WARNING, "Configuration parameter is to large  (overflow), falling back to default");
        return fallback;
    }
    
    if(unsignedint) {
        if(result > UINT_MAX || result < 0) {
            syslog(LOG_WARNING, "Parsed string is not within unsigned integer range");
            return fallback;
        }
    } else {
        /* Parse as signed integer */
        if(result > INT_MAX || result < INT_MIN) {
            syslog(LOG_WARNING, "Parsed string is not within signed integer range");
            return fallback;
        }
    }
    
    if(end == string) {
        syslog(LOG_WARNING, "String is not numeric");
        return fallback;
    }
    
    if('\0' != *end) {
        syslog(LOG_WARNING, "parseint got extra characters on input line");
        return fallback;
    }
    
    return (int) result;
}


config* conf = NULL;

/**
 * Parse configuration file at /etc/config/dpt-connector
 * @return true when parse was successfull
 */
bool config_parse() {
    /* Read buffer */
    char buffer[CONFIG_BUFF_SIZE];
    char* cfgl;
    FILE * fd;
    char* key;
    char* value;
    errno = 0;
    
    printf("Starting to parse configuration\r\n");
    
    /* Reserve memory for configuration and null terminate every string */
    if(conf == NULL) {
        conf = (config*) calloc(1, sizeof(config));
        
        /* Put in default configuration */
        conf->daemon = FORK_ON_START;
#ifdef DEBUG
        printf("conf->daemon = %s\r\n", FORK_ON_START ? "true" : "false");
#endif
        
        conf->platform_url = strmalloc(conf->platform_url, PLATFORM_BASE_ADDRESS);
#ifdef DEBUG
        printf("conf->platfrom_url = %s\r\n", conf->platform_url);
#endif
        
        conf->ssh_path = strmalloc(conf->ssh_path, SSH_PATH);
#ifdef DEBUG  
        printf("conf->ssh_path = %s\r\n", conf->ssh_path);
#endif
          
        conf->null_path = strmalloc(conf->null_path, PATH_DEVNULL);
#ifdef DEBUG
        printf("conf->null_path = %s\r\n", conf->null_path);
#endif
         
        conf->ssh_poll_time = POLL_TIME;
#ifdef DEBUG 
        printf("conf->ssh_poll_time = %d\r\n", conf->ssh_poll_time);
#endif
        
        conf->ssl_cert_path = strmalloc(conf->ssl_cert_path, CURL_SSL_ROOT_CERT_PATH);
#ifdef DEBUG 
        printf("conf->ssl_cert_path = %s\r\n", conf->ssl_cert_path);
#endif

        /* Make sure the essentials are initialized */
        conf->typeid = strmalloc(conf->typeid, "");
#ifdef DEBUG 
        printf("conf->typeid = %s\r\n", conf->typeid);
#endif
        
        conf->devid = strmalloc(conf->devid, "");
#ifdef DEBUG 
        printf("conf->devid = %s\r\n", conf->devid);
#endif
        
        conf->devkey = strmalloc(conf->devkey, "");
#ifdef DEBUG 
        printf("conf->devkey = %s\r\n", conf->devkey);
#endif
    }

    if ((fd = fopen("/etc/config/dpt-connector", "r")) != NULL) {
#ifdef DEBUG 
        printf("Opened configruation file: /etc/config/dpt-connector\r\n");
#endif
        
        while ((cfgl = fgets(buffer, CONFIG_BUFF_SIZE - 1, fd)) != NULL) {
            /* Ignore lines starting with '#', ';' or whitespace  */
            if (cfgl[0] != '#' && cfgl[0] != ';' && cfgl[0] != ' ' && cfgl[0] != '\t' && cfgl[0] != '\r' && cfgl[0] != '\n') {
                char* trimmed = trimwhitespace(buffer);
                key = strtok(trimmed, " \t");
                value = strtok (NULL, " ,-");

#ifdef DEBUG 
        printf("Parsing configuration line '%s' = '%s'\r\n", key, value);
#endif                
                if(key != NULL && value != NULL) {
                    if(strcmp(key, "daemon") == 0) 
                    {
                        conf->daemon = value[0] == 't';
                    } 
                    else if (strcmp(key, "typeid") == 0) 
                    {
                        conf->typeid = strmalloc(conf->typeid, value);
                    } 
                    else if (strcmp(key, "devid") == 0)
                    {
                        conf->devid = strmalloc(conf->devid, value);
                    }
                    else if (strcmp(key, "devkey") == 0)
                    {
                        conf->devkey = strmalloc(conf->devkey, value);
                    }
                    else if (strcmp(key, "platform_base_address") == 0)
                    {
                        conf->platform_url = strmalloc(conf->platform_url, value);
                    }
                    else if (strcmp(key, "ssh_path") == 0)
                    {
                        conf->ssh_path = strmalloc(conf->ssh_path, value);
                    }
                    else if (strcmp(key, "null_path") == 0)
                    {
                        conf->null_path = strmalloc(conf->null_path, value);
                    }
                    else if (strcmp(key, "ssh_poll_time") == 0)
                    {
                        conf->ssh_poll_time = parseint(value, true, POLL_TIME);
                    }
                    else if(strcmp(key, "curl_root_cert_path") == 0)
                    {
                        conf->ssl_cert_path = strmalloc(conf->ssl_cert_path, value);
                    }
                    else 
                    {
                        syslog(LOG_WARNING, "Unknown configuration option: '%s'", key);
                    }
                }
            }
        }

        if (errno != 0) {
            free(conf);
            fclose(fd);
            syslog(LOG_ERR, "Could not reload configuration: %s", strerror(errno));
            return false;
        }
        syslog(LOG_INFO, "Successfully reloaded dpt-connector configuration");
        fclose(fd);
        return true;
    }
    
    syslog(LOG_ERR, "Could not reload configuration: config file not found");
    return false;
}

/**
 * Returns true if the configuration file has a filled 
 * in typeid, devid and devkey. 
 * @return true if the config is ready, false otherways. 
 */
bool config_ready() {
    if(strlen(conf->typeid) != DPT_TYPE_ID_SIZE) {
        return false;
    }
    
    if(strlen(conf->devid) != DPT_DEVICE_ID_SIZE) {
        return false;
    }
    
    if(strlen(conf->devkey) != DPT_DEVICE_KEY_SIZE) {
        return false;
    }
    
    if(strlen(conf->ssl_cert_path) < 2) {
        return false;
    }

#ifdef DEBUG
    printf("Configuration is ready\r\n");
#endif    
    /* Configuration is correct and ready */
    return true;
}

/**
 * Free the parsed configuration data
 */
void config_free() {
    free(conf->devid);
    free(conf->devkey);
    free(conf->null_path);
    free(conf->platform_url);
    free(conf->ssh_path);
    free(conf->typeid);
    free(conf);
}
