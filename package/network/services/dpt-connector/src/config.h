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
 * File:   config.h
 * Created on November 5, 2014, 1:14 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <stdint.h>
#include <stdbool.h>

#define DEBUG                                                                   /* The application will log debug messages if defined */
#define NO_SSL_CHECK                                                            /* Curl will not check the SSL certificate validity */
#define FORK_ON_START               false                                       /* Do not fork when configuratin file could not be found */

/* Platform settings */
#define PLATFORM_BASE_ADDRESS       "platform.bluecherry.io"                    /* The DNS name of the BlueCherry platform */

/* Path settings */
#define SSH_PATH                    "/usr/bin/ssh"                              /* Path to OpenSSH client */                             
#define PATH_DEVNULL                "/dev/null"                                 /* Path to discard file */

/* SSH monitor settings */
#define POLL_TIME                   20                                          /* Check SSH connection every 20 seconds */

/* Config parser settings */
#define CONFIG_BUFF_SIZE            512                                         /* Maximum number of bytes on 1 config line */

/* Curl settings */
#define CURL_SSL_ROOT_CERT_PATH     "/etc/curlssl/cacert.pem"                   /* Default curl root certificate path */
#define CURL_USER_AGENT             "dpt-connector/1.0"                         /* The DPT-Connector agent */

/* Fixed configuration parameters */
#define DPT_TYPE_ID_SIZE            8
#define DPT_DEVICE_ID_SIZE          8
#define DPT_DEVICE_KEY_SIZE         128

/* Configuration structure */
typedef struct{
    bool daemon;
    char* typeid;
    char* devid;
    char* devkey;
    char* platform_url;
    char* ssh_path;
    char* null_path;
    char* ssl_cert_path;
    int ssh_poll_time;
} config;

/* Application wide configuration */
extern config* conf;

/**
 * Parse configuration file at /etc/config/dpt-connector
 * @return true when parse was successfull
 */
bool config_parse();

/**
 * Free the parsed configuration data
 */
void config_free();

/**
 * Returns true if the configuration file has a filled 
 * in typeid, devid and devkey. 
 * @return true if the config is ready, false otherways. 
 */
bool config_ready();
#endif

