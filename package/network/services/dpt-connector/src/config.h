/**
 * @file config.h
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
 * This file contains the public methods and constants of the configuration module which
 * parses the JSON configuration file at start-up and loads the complete configuration
 * in memory so it can be accessed fast at run-time.
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <stdbool.h>

#include "log.h"

/**
 * @defgroup CONFIG Compile time configuration.
 * @{
 */

/**
 * @brief The interval in seconds to check the BlueCherry connection.
 */
#define CONFIG_SSH_CONN_POLL_TIME                   5

/** @}*/

/**
 * @brief The application configuration parameters.
 * 
 * This structure contains all the parameters the application will use. This
 * structure will be created one at start-up and it will be kept in memory 
 * until the application stops.
 */
struct config {
    bool daemonize;             /**< When this boolean is true the application will run in the background */
    int ssh_poll_time;          /**< The SSH connection poll time */
    char *bluecherry_address;   /**< The address of the IoT platform */
    char *ssh_path;             /**< The path of the OpenSSH deaemon */
    char *ssh_keygen_path;      /**< The path of the OpenSSH key generator */
    enum log_level loglevel;    /**< The application logging level priority */
    FILE *logfile;              /**< The path of the application logfile */
    bool log_to_syslog;         /**< When this is true, the logger should ignore the logfile and write to syslog */
    char *pidfile;              /**< The filepath to write the PID in on start-up */
    char *identity_file;        /**< The SSH identity file to use */
    char *identity_file_pub;    /**< The SSH public identity file */
    char *ipc_file;             /**< The filepath to write the IPC status to */
};

/**
 * @brief The application wide configuration.
 * 
 * This external variable is accessible from all source files and contains
 * the current in memory copy of the application configuration.
 */
extern struct config *appconf;

bool config_load(const char *path);

bool config_reload(const char *path);

void config_destroy();

#endif