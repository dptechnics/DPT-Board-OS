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
 * File:   main.c
 * Created on 4/11/2014
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "dptnetwork.h"
#include "logger.h"
#include "ssh.h"
#include "config.h"

int main(void) {
    int cur_fd;
    
    /* Initialise system log and load configuration */
    log_init();
    config_parse();

    /* Daemonize if asked */
    if (conf->daemon) {
        switch (fork()) {
            case -1:
                perror("fork()");
                exit(1);

            case 0:
                /* Daemon setup */
                if (chdir("/"))
                    perror("chdir()");
                
                /* Redirect all output to null */
                cur_fd = open("/dev/null", O_WRONLY);
                if (cur_fd > 0) {
                    dup2(cur_fd, 0);
                    dup2(cur_fd, 1);
                    dup2(cur_fd, 2);
                }

                break;

            default:
                exit(0);
        }
    }

    /* Start the SSH connection */
    ssh_init();
    ssh_start_data_connection();
    
    /* Free configuration parameters and close log */
    config_free();
    log_close();
    
    return 0;
}
