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
 * File:   ssh.h
 * Created on March 7, 2015, 3:48 AM
 */

#ifndef SSH_H
#define	SSH_H

#include <poll.h>
#include <stddef.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <stdbool.h>

#include "dptnetwork.h"

/* SSH connection monitor states */
#define P_CONTINUE                  0                                           /* Do nothing and continue connection monitoring */
#define P_RESTART                   1                                           /* Restart the SSH child process */
#define P_EXIT                      2                                           /* Exit the program  */

/**
 * Initialize SSH connection monitor
 */
void ssh_init();

/**
 * Wait for an active connection to BlueCherry
 */
void ssh_internet_wait();

/**
 * Get an SSH server to connect to. 
 * @param serv the server structure to fill up. 
 */
void ssh_get_server(ssh_server *serv);

/**
 * Overwrite or create a known hosts file with an entry
 * for the server parameters given to this server. 
 * @param ip the IP of the remote host. 
 * @param port the port of the remote host. 
 * @param key the hostkey. 
 * @return true on success, false on error.
 */
bool ssh_set_known_host(char *ip, int port, char *key);

/**
 * Start the SSH data connection. This connection
 * will also be used to tunnel the connection to the
 * DPT-Monitor.
 */
void ssh_start_data_connection();

/**
 * Watch the SSH connection based on OpenSSH signals and exit codes. 
 * @return control code on what to do with the child SSH process. 
 */
int ssh_watch();

/**
 * Wait for the OpenSSH child process to change state. This function
 * returns immediately when the child process did not exit. 
 * @return control code on what to do with this signal. 
 */
int ssh_wait();

/**
 * Kill the SSH child process
 */
void ssh_kill();

/**
 * Handler for signals from the kernel. 
 * @param sig the number of the signal. 
 */
void ssh_signal_handler(int sig);

/**
 * Exit the program/fork with an error
 */
void ssh_exit_with_error();

#endif

