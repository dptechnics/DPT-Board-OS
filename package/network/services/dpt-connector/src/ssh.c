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
 * File:   ssh.c
 * Created on March 7, 2015, 7:06 AM
 */

#include "ssh.h"
#include "config.h"
#include "logger.h"
#include "dptnetwork.h"

#include <sys/types.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <sys/wait.h>
#include <setjmp.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <inttypes.h>
#include <sys/syslog.h>

int con_pid;                                /* The SSH connection PID */
volatile sig_atomic_t restart_ssh;          /* When 1 the SSH connection must be restarted */
volatile sig_atomic_t canlongjmp;           /* When 1 when we can do a long jmp */
sigjmp_buf jumpbuf;                         /* Buffer to save the current environment in */

/**
 * Initialize SSH connection monitor
 */
void ssh_init() {
    /* Set up signal interrupt handler */
    struct sigaction act;

    act.sa_handler = ssh_signal_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGHUP, &act, NULL);
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
    sigaction(SIGCHLD, &act, NULL);

    act.sa_flags |= SA_RESTART;
    sigaction(SIGALRM, &act, NULL);
}

/**
 * Wait for an active connection to BlueCherry
 */
void ssh_internet_wait() {
    while(!dptnet_check_bluecherry_conn()) {
        sleep(1);
#ifdef DEBUG
        printf("No access to BlueCherry platform\r\n");
#endif
    } 
#ifdef DEBUG
    printf("Route to BlueCherry platform is available\r\n");
#endif
    syslog(LOG_INFO, "Route to BlueCherry platform is available");
}

/**
 * Get an SSH server to connect to. 
 * @param serv the server structure to fill up. 
 */
void ssh_get_server(ssh_server *serv) {
    while (true) {
#ifdef DEBUG
        printf("Requesting BlueCherry SSH node...\r\n");
#endif
        
        /* Reload configuration */
        if (config_parse()) {
#ifdef DEBUG
        printf("... parsing configuration complete\r\n");
#endif
            /* Only try to connect when config is ready */
            if (config_ready()) {
#ifdef DEBUG
        printf("... configuration is 100%% complete, requestng SSH server...\r\n");
#endif
                /* Request port from server until it works */
                if(dptnet_request_ssh_server(serv)) {
                    /* Set known hosts configuration */
                    ssh_set_known_host(serv->ipv4, serv->serverport, serv->hostkey);
                    
                    return;
                }
            } else {
#ifdef DEBUG
                printf("BlueCherry configuration is not ready\r\n");
#endif
            }
        } else {
#ifdef DEBUG
            printf("Could not parse configuration, trying again in 5 seconds\r\n");
#endif
        }

        /* Wait 5 seconds before retrying */
        sleep(5);
    }
}

/**
 * Overwrite or create a known hosts file with an entry
 * for the server parameters given to this server. 
 * @param ip the IP of the remote host. 
 * @param port the port of the remote host. 
 * @param key the hostkey. 
 * @return true on success, false on error.
 */
bool ssh_set_known_host(char *ip, int port, char *key)
{
    FILE* file = fopen("/root/.ssh/known_hosts", "w");
    if(file == NULL) {
        return false;
    }
    
    fprintf(file, "[%s]:%d %s\n", ip, port, key);
    fclose(file);
    
    return true;
}

/**
 * Start the SSH data connection. This connection
 * will also be used to tunnel the connection to the
 * DPT-Monitor.
 */
void ssh_start_data_connection() {
    char location[64] = {0};
    char rtunnel[32] = {0};
    char ssh_port[16] = {0};
    ssh_server serv;

    while (1) {
        restart_ssh = 0;

        /* Wait for internet connection */
        ssh_internet_wait();

        /* Wait for SSH data port */
        ssh_get_server(&serv);

        /* Format the connection arguments */
        sprintf(rtunnel, "0.0.0.0:%d:localhost:80", serv.port);
        sprintf(location, "%s.%s@%s", conf->typeid, conf->devid, serv.ipv4);
        sprintf(ssh_port, "%d", serv.serverport);

        char* arg[] = {
            conf->ssh_path,
            "-p", ssh_port,
            "-R", rtunnel,
            "-N",
            "-o ServerAliveInterval 60",
            "-o ServerAliveCountMax 2",
            location,
            NULL
        };

        con_pid = fork();
        switch (con_pid) {
            case 0:
                syslog(LOG_DEBUG, "Starting SSH data connection");

                /* Start SSH data connection */
                execvp(arg[0], arg);

                /* Exit the fork process with an error */
                syslog(LOG_ERR, "SSH data connection failed with error: %s", strerror(errno));
                ssh_exit_with_error();

                /* If we don't do this the loop could restart */
                kill(SIGTERM, getppid());
                exit(1);
                break;
            case -1:
                con_pid = 0;
                syslog(LOG_ERR, "Could not fork parent process: %s", strerror(errno));
                ssh_exit_with_error();
                break;
            default:
                syslog(LOG_INFO, "SSH data connection spawned with pid: %d", con_pid);
                if (ssh_watch() == P_EXIT)
                    return;
                break;
        }
    }
}

/**
 * Watch the SSH connection based on OpenSSH signals and exit codes. 
 * @return control code on what to do with the child SSH process. 
 */
int ssh_watch() {
    int r;
    int val;
    int secs_left;

    while (true) {
        /* Check if we need to restart SSH */
        if (restart_ssh) {
            syslog(LOG_INFO, "DPT-Connector is restarting the SSH connection");
            ssh_kill();
            return P_RESTART;
        }


        if ((val = sigsetjmp(jumpbuf, 1)) == 0) {
            syslog(LOG_DEBUG, "Checking SSH data connection with PID: %d", con_pid);

            /* Wait for a signal from the child SSH connection */
            r = ssh_wait(WNOHANG);
            if (r != P_CONTINUE) {
                syslog(LOG_DEBUG, "SSH connection is no longer working, action: %d", r);
                return r;
            }

            /* Reset all alarms for DPT-monitor and reset them */
            secs_left = alarm(0);
            if (secs_left == 0)
                secs_left = POLL_TIME;
            alarm(secs_left);

            syslog(LOG_DEBUG, "New SSH connection check in %d seconds", secs_left);

            /* Wait for the alarm */
            canlongjmp = 1;
            pause();
        } else {
            switch (val) {
                case SIGINT:
                case SIGTERM:
                case SIGQUIT:
                case SIGABRT:
                    syslog(LOG_INFO, "Received signal to exit (%d)", val);
                    ssh_kill();
                    return P_EXIT;
                    break;
                case SIGALRM:
                default:
                    break;
            }
        }
    }
}

/**
 * Wait for the OpenSSH child process to change state. This function
 * returns immediately when the child process did not exit. 
 * @return control code on what to do with this signal. 
 */
int ssh_wait() {
    int status;
    int evalue;

    /* Block until the SSH connection changed state */
    if (waitpid(con_pid, &status, WNOHANG) > 0) {
        if (WIFSIGNALED(status)) {
            switch (WTERMSIG(status)) {
                case SIGINT:
                case SIGTERM:
                case SIGKILL:
                    /* Exit when the SSH child was interrupted, killed or terminated */
                    syslog(LOG_INFO, "SSH exited on signal %d, dpt-connector is also exiting", WTERMSIG(status));
                    return P_EXIT;
                    break;
                default:
                    /* Restart on any other signal */
                    syslog(LOG_INFO, "SSH exited on signal %d, restarting SSH", WTERMSIG(status));
                    return P_RESTART;
                    break;
            }
        } else if (WIFEXITED(status)) {
            evalue = WEXITSTATUS(status);

            switch (evalue) {
                case 255:
                case 1:
                    syslog(LOG_INFO, "SSH exited with error status %d, restarting SSH", evalue);
                    return P_RESTART;
                case 0:
                default:
                    syslog(LOG_ERR, "SSH exited with status %d, DPT-Connector is exiting", evalue);
                    return P_EXIT;
                    break;
            }
        }
    }

    /* Continue monitoring */
    return P_CONTINUE;
}

/**
 * Kill the SSH child process
 */
void ssh_kill(void) {
    int w;
    int status;

    if (con_pid) {
        kill(con_pid, SIGTERM);

        /* Active wait until the child exits */
        do {
            errno = 0;
            w = waitpid(con_pid, &status, 0);
        } while (w < 0 && errno == EINTR);

        if (w <= 0) {
            syslog(LOG_ERR, "Could not kill SSH connection: %s", strerror(errno));
        }
    }
}

/**
 * Handler for signals from the kernel. 
 * @param sig the number of the signal. 
 */
void ssh_signal_handler(int sig) {
    if (canlongjmp) {
        canlongjmp = 0;
        siglongjmp(jumpbuf, sig);
    }
}

/**
 * Exit the fork with an error
 */
void ssh_exit_with_error() {
    ssh_kill();
    _exit(1);
}
