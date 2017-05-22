/**
 * @file config.c
 * @author Daan Pape <daan@dptechnics.com>
 * @date 6 Mar 2016
 * @copyright DPTechnics
 * @brief DPT-connector daemon configuration module
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
 * This file contains the implementation of the configuration module which
 * parses the JSON configuration file at start-up and loads the complete configuration
 * in memory so it can be accessed fast at run-time.
 */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <json-c/json.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>
#include <malloc.h>

#include "config.h"

/**
 * @brief The size of the configuration file buffer.
 */
#define CONFIG_BUFF_SIZE        4096

/**
 * @brief The application wide configuration structure.
 */
struct config *appconf = NULL;

/**
 * @brief Load the configuration file.
 * 
 * This function will read the configuration JSON file and parse it into the 
 * application wide @ref appconf structure. After this function is called the
 * configuration struct must be deleted with the @ref config_destroy function.
 * 
 * The config file has the following structure:
 * @code
 * {
 *    "daemonize" : true/false,
 *    "ssh_poll_time" : 0-100,
 *    "bluecherry_address" : "url.to.iot.server",
 *    "ssh_path" : "/usr/bin/ssh",
 *    "ssh_keygen_path" : "/usr/bin/ssh-keygen",
 *    "loglevel" : "NONE/ERROR/WARNING/INFO/DEBUG",
 *    "logfile" : "/tmp/path/to/logfile",
 *    "pid_file" : "/path/to/pidfile.pid",
 *    "identity_file" : "/path/to/id_rsa",
 *    "ipc_path" : "/path/to/ipc_file"
 * }
 * @endcode
 * 
 * @param path The path where to find the configuration JSON file.
 * 
 * @return True if the configuration could be parsed successfully.
 */
bool config_load(const char *path)
{
    appconf = (struct config*) malloc(sizeof(struct config));
    if(appconf == NULL) {
        log_basic(stderr, LG_ERROR, "There was not enough memory to reserve the configuration memory\n");
        return false;
    }
    
    return config_reload(path);
}

/**
 * @brief Reload the application wide configuration structure.
 * 
 * This function will read the configuration JSON file and parse it into the 
 * already existing application wide @ref appconf structure. This function can
 * only be used if the @ref config_load function has been called earlier.
 * 
 * @param path The path where to find the configuration JSON file.
 * 
 * @return True if the configuration structure could be parsed successfully.
 */
bool config_reload(const char *path)
{
    /* Check if the appconf structure has already been allocated */
    if(appconf == NULL) {
        return false;
    }
    
    /* Try to open the configuration file */
    FILE *fp = fopen(path, "r");
    if(fp == NULL) {
        return false;
    }
    
    char buff[CONFIG_BUFF_SIZE];
    size_t len = fread(buff, sizeof(char), CONFIG_BUFF_SIZE, fp);
    if(len == 0) {
        log_basic(stderr, LG_ERROR, "The configuration file '%s' was empty\n", path);
        fclose(fp);
        return false;
    } else if(len >= CONFIG_BUFF_SIZE) {
        log_basic(stderr, LG_ERROR, "The configuration file is to big for the config buffer (%dB)\n", CONFIG_BUFF_SIZE);
        fclose(fp);
        return false;
    }
    
    /* 0-terminate the buffer and close the config file */
    buff[len] = '\0';
    fclose(fp);
    
    /* Try to parse the configuration file */
    json_object *j_config = json_tokener_parse(buff);
    if(json_object_is_type(j_config, json_type_null)) {
        log_basic(stderr, LG_ERROR, "The configuration file could not be parsed\n");
        return false;
    }
    
    json_object *j_daemonize;
    json_object *j_ssh_poll_time;
    json_object *j_bluecherry_address;
    json_object *j_ssh_path;
    json_object *j_ssh_keygen_path;
    json_object *j_loglevel;
    json_object *j_logfile;
    json_object *j_pid_file;
    json_object *j_identity_file;
    json_object *j_ipc_file_path;
    
    if(!json_object_object_get_ex(j_config, "daemonize", &j_daemonize) ||
       !json_object_object_get_ex(j_config, "ssh_poll_time", &j_ssh_poll_time) ||
       !json_object_object_get_ex(j_config, "bluecherry_address", &j_bluecherry_address) ||
       !json_object_object_get_ex(j_config, "ssh_path", &j_ssh_path) ||
       !json_object_object_get_ex(j_config, "ssh_keygen_path", &j_ssh_keygen_path) ||
       !json_object_object_get_ex(j_config, "loglevel", &j_loglevel) ||
       !json_object_object_get_ex(j_config, "logfile", &j_logfile) ||
       !json_object_object_get_ex(j_config, "pid_file", &j_pid_file) ||
       !json_object_object_get_ex(j_config, "identity_file", &j_identity_file) ||
       !json_object_object_get_ex(j_config, "ipc_path", &j_ipc_file_path))
    {
        json_object_put(j_config);
        log_basic(stderr, LG_ERROR, "The configuration file syntax is malformed or incomplete\n");
        return false;
    }
    
    /* Read out if this application should run as a daemon or not */
    appconf->daemonize = json_object_get_boolean(j_daemonize);
    
    /* Read out SSH poll time */
    appconf->ssh_poll_time = json_object_get_int(j_ssh_poll_time);
    
    /* Read out the BlueCherry server address  */
    const char* bluecherry_address = json_object_get_string(j_bluecherry_address);
    size_t bc_addr_len = strlen(bluecherry_address);
    if(bc_addr_len <= 0) {
        log_basic(stderr, LG_ERROR, "The BlueCherry server URL is empty and required\n");
        json_object_put(j_config);
        return false;
    }
    appconf->bluecherry_address = (char*) realloc(appconf->bluecherry_address, (bc_addr_len + 1) * sizeof(char));
    memcpy(appconf->bluecherry_address, bluecherry_address, bc_addr_len);
    appconf->bluecherry_address[bc_addr_len] = '\0';
    
    /* Read out the SSH path */
    const char* ssh_path = json_object_get_string(j_ssh_path);
    size_t ssh_path_len = strlen(ssh_path);
    if(ssh_path_len <= 0) {
        log_basic(stderr, LG_ERROR, "The OpenSSH path is empty and required\n");
        json_object_put(j_config);
        return false;
    }
    appconf->ssh_path = (char*) realloc(appconf->ssh_path, (ssh_path_len + 1) * sizeof(char));
    memcpy(appconf->ssh_path, ssh_path, ssh_path_len);
    appconf->ssh_path[ssh_path_len] = '\0';
    
    /* Read out the SSH keygen path */
    const char* ssh_keygen_path = json_object_get_string(j_ssh_keygen_path);
    size_t ssh_keygen_path_len = strlen(ssh_keygen_path);
    if(ssh_keygen_path_len <= 0) {
        log_basic(stderr, LG_ERROR, "The OpenSSH keygen path is empty and required\n");
        json_object_put(j_config);
        return false;
    }
    appconf->ssh_keygen_path = (char*) realloc(appconf->ssh_keygen_path, (ssh_keygen_path_len + 1) * sizeof(char));
    memcpy(appconf->ssh_keygen_path, ssh_keygen_path, ssh_keygen_path_len);
    appconf->ssh_keygen_path[ssh_keygen_path_len] = '\0';

    /* Read out the application wide logging level */
    const char* loglevel = json_object_get_string(j_loglevel);
    if(strlen(loglevel) <= 0) {
        log_basic(stderr, LG_ERROR, "The configuration file did not contain a valid logging level, falling back to LOG_ERROR\n");
        appconf->loglevel = LG_ERROR;
    }
    switch(loglevel[0]) {
        case 'N':
            appconf->loglevel = LG_NONE;
            break;
        case 'E':
            appconf->loglevel = LG_ERROR;
            break;
        case 'W' :
            appconf->loglevel = LOG_WARNING;
            break;
        case 'I':
            appconf->loglevel = LOG_INFO;
            break;
        case 'D':
            appconf->loglevel = LOG_DEBUG;
            break;
        default:
            log_basic(stderr, LG_ERROR, "The configuration file did not contain a valid logging level, falling back to LOG_ERROR\n");
            appconf->loglevel = LG_ERROR;
            break;
    }
    
    /* Read out the path of the logfile and open it if necessary */
    const char* logfile = json_object_get_string(j_logfile);
    appconf->log_to_syslog = false;
    
    if(strlen(logfile) == 0) {
        /* Fall back to stdout if the path is empty */
        appconf->logfile = stdout;
    } else {
        if(strcmp(logfile, "stdout") == 0) {
            appconf->logfile = stdout;
        } else if(strcmp(logfile, "stderr") == 0) {
            appconf->logfile = stderr;
        } else if(strcmp(logfile, "syslog") == 0) {
            appconf->logfile = NULL;
            appconf->log_to_syslog = true;
            
            /* Open the syslogger for this app */
            openlog("DPT-connector", LOG_CONS | LOG_PID, LOG_DAEMON);
            
        } else {
            appconf->logfile = fopen(logfile, "a");
            if(appconf->logfile == NULL) {
                /* When the logfile could not be opened and/or created, use stdout */
                appconf->logfile = stdout;
                log_basic(stderr, LG_ERROR, "The logfile '%s' could not be opened\n", logfile);
            }
        }
    }
    
    /* Read out the PID file path */
    const char* pid_filepath = json_object_get_string(j_pid_file);
    size_t pid_filepath_len = strlen(pid_filepath);
    if(pid_filepath_len <= 0) {
        log_basic(stderr, LG_ERROR, "The pid file path is required");
        json_object_put(j_config);
        return false;
    }
    appconf->pidfile = (char*) realloc(appconf->pidfile, (pid_filepath_len + 1) * sizeof(char));
    memcpy(appconf->pidfile, pid_filepath, pid_filepath_len);
    appconf->pidfile[pid_filepath_len] = '\0';
    
    /* Read out the identity file path */
    const char* identity_filepath = json_object_get_string(j_identity_file);
    size_t identity_filepath_len = strlen(identity_filepath);
    if(identity_filepath_len <= 0) {
        log_basic(stderr, LG_ERROR, "The identity file path is required");
        json_object_put(j_config);
        return false;
    }
    appconf->identity_file = (char*) realloc(appconf->identity_file, (identity_filepath_len + 1) * sizeof(char));
    memcpy(appconf->identity_file, identity_filepath, identity_filepath_len);
    appconf->identity_file[identity_filepath_len] = '\0';
    
    /* Create the public filename */
    size_t identity_file_pub_len = identity_filepath_len + strlen(".pub");
    appconf->identity_file_pub = (char*) realloc(appconf->identity_file_pub, (identity_file_pub_len + 1) * sizeof(char));
    snprintf(appconf->identity_file_pub, identity_file_pub_len + 1, "%s.pub", appconf->identity_file);
    
    /* Read out the IPC file path */
    const char* ipc_file_path = json_object_get_string(j_ipc_file_path);
    size_t ipc_file_path_len = strlen(ipc_file_path);
    if(ipc_file_path_len <= 0) {
        log_basic(stderr, LG_ERROR, "The IPC file path is required");
        json_object_put(j_config);
        return false;
    }
    appconf->ipc_file = (char*) realloc(appconf->ipc_file, (ipc_file_path_len + 1) * sizeof(char));
    memcpy(appconf->ipc_file, ipc_file_path, ipc_file_path_len);
    appconf->ipc_file[ipc_file_path_len] = '\0';
    
    /* Release parsed JSON and return */
    json_object_put(j_config);
    return true;
}

/**
 * @brief Destroy the application wide configuration.
 * 
 * This function will release the memory used by the application wide configuration.
 * 
 * @return None
 */
void config_destroy()
{
    if(appconf == NULL) {
        return;
    }
    
    /* Close logfile entries */
    if(appconf->logfile != stdout) {
        fclose(appconf->logfile);
    }
    
    free(appconf->bluecherry_address);
    free(appconf->ssh_path);
    free(appconf->pidfile);
    
    /* Release the memory */
    free(appconf);
    appconf = NULL;
}