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
#include <stdbool.h>
#include <fcntl.h>
#include <sys/reboot.h>

#define DAEMON              true
#define TIMER_SLEEP         10
#define TIMER_HOLDOFF       120
#define COMMAND_STR         "pidof %s"

/**
 * Reboot the system when something goes wrong.
 */
static inline void wd_sys_reboot()
{
    /* Synchronize buffers */
    sync();
    
    /* Perform a hard reset now*/
    reboot(RB_AUTOBOOT);
}

/**
 * Check if a program is running or not. Returns true
 * when it's running and false if it's not. 
 * @param progname the name of the program to check. 
 * @return true if running false if not. 
 */
static bool wd_check(const char* progname)
{
    char command[1024];
    
    /* Prepare the command buffer */
    snprintf(command, 1024, COMMAND_STR, progname);

    return system(command) == 0;
}

/**
 * Checks if the given processes are still running and 
 * if not resets the system. 
 */
static void wd_timer() 
{
    while(true) {
        
        /* Check for the breakout server*/
        if(!wd_check("dpt-breakout-server")) {
#ifndef DAEMON
            printf("dpt-breakout-server is not running\r\n");
#endif
            wd_sys_reboot();
        }
        
        /* Check for the dpt-connector*/
        if(!wd_check("dpt-connector")) {
#ifndef DAEMON
            printf("dpt-connector is not running\r\n");
#endif
            wd_sys_reboot();
        }

#ifndef DAEMON        
        printf("All DPT-Programs running, all ok\r\n");
#endif
        sleep(TIMER_SLEEP);
    }
}

int main(void) {
#ifdef DAEMON
    int cur_fd;

    /* Daemonize if asked */

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
#endif
    
    /* Start the watchdog after hold time */
    sleep(TIMER_HOLDOFF);
    wd_timer();
    
    return 0;
}
