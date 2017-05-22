/**
 * @file main.c
 * @author Daan Pape <daan@dptechnics.com>
 * @date 4 Nov 2016
 * @copyright DPTechnics
 * @brief DPT-connector IoT-connector 
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
 * This file contains the main entrypoint of the DPTechnics BlueCherry 
 * Internet-of-Things connector.
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

#include "network.h"
#include "log.h"
#include "ssh.h"
#include "config.h"
#include "device.h"

/**
 * @brief DPT-connector IoT daemon.
 * 
 * This function is  the entrypoint for the DPT-connector software which
 * set's up and maintains a BlueCherry platform connection.
 * 
 * @param argc The number of command line arguments.
 * @param argv An array containing the command line arguments as strings.
 * 
 * @return @c EXIT_SUCCESS when ended properly, @c EXIT_FAILURE on error
 */
int main(int argc, char *argv[]) {
    
    /* Check if the configuration file is given as a program argument  */
    if(argc != 2 && argc != 3) {
        log_basic(stderr, LG_ERROR, "Usage: %s <configfile> or %s setbcflag true/false\n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }
    
    /* The program is used to set the activation flag */
    if(argc == 3) {
        if(strcmp("setbcflag", argv[1]) == 0) {
            bool state = false;
            
            if(strcmp("true", argv[2]) == 0) {
                state = true;
            } else if(strcmp("false", argv[2]) == 0) {
                state = false;
            } else {
                log_basic(stderr, LG_ERROR, "Usage: %s <configfile>\n or %s setbcflag true/false\n", argv[0], argv[0]);
                return EXIT_FAILURE;
            }
            
            /* Set the state */
            if(device_set_bluecherry_active(state)) {
                log_basic(stdout, LG_INFO, "BlueCherry connection flag is %s\n\n", state ? "enabled" : "disabled");
                return EXIT_SUCCESS;
            } else {
                log_basic(stderr, LG_ERROR, "Could not set the BlueCherry connection flag to %s\n\n", state ? "enabled" : "disabled");
                return EXIT_FAILURE;
            }
        }
        
        log_basic(stderr, LG_ERROR, "Usage: %s <configfile> or %s setbcflag true/false\n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }
    
    /* Try to load the application configuration */
    if(!config_load(argv[1])) {
        log_basic(stderr, LG_ERROR, "The application configuration could not be loaded\n");
        return EXIT_FAILURE;
    }
    
    /* Daemonize if asked */
    if(appconf->daemonize) {  
        int o_fd = -1;
        
        switch(fork()) {
            case -1:
                log_event(LG_ERROR, "Could not create application fork, exiting\n");
                return EXIT_FAILURE;
                
            case 0:
                /* Change working directory from child */
                if(chdir("/tmp")) {
                    log_event(LG_ERROR, "Could not change working directory, exiting\r\n");
                    return EXIT_FAILURE;
                }
                
                /* Open output file and redirect TTY's */
                o_fd = open("/dev/null", O_WRONLY);
                if(o_fd < 0) {
                    log_event(LG_ERROR, "Could not open deamon TTY file '%s', reason %d: %s, exiting\r\n", "/dev/null", errno, strerror(errno));
                    return EXIT_FAILURE;
                }
                dup2(o_fd, 0);
                dup2(o_fd, 1);
                dup2(o_fd, 2); 
                break;
                
            default:
                return EXIT_FAILURE;
        }
    }
    
    /* Write PID of the process to the PID file */
    pid_t pid = getpid();
    FILE *pidfile = fopen(appconf->pidfile, "w+");
    if(pidfile == NULL) {
        log_event(LG_ERROR, "Could not write PID to pidfile: %s\n", appconf->pidfile);
        return EXIT_FAILURE;
    }
    fprintf(pidfile, "%d", (int) pid);
    fclose(pidfile);

    /* Start the SSH connection */
    ssh_init();
    ssh_start_data_connection();
    
    /* If syslog was used, close it */
    if(appconf->log_to_syslog) {
        closelog();
    }
    
    /* Free configuration parameters and close log */
    config_destroy();
    
    return EXIT_SUCCESS;
}
