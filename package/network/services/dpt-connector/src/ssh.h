/**
 * @file ssh.h
 * @author Daan Pape <daan@dptechnics.com>
 * @date 7 Mar 2015
 * @copyright DPTechnics
 * @brief DPT-connector IoT-connector SSH connection functions 
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
 * This file contains all the SSH related functions needed for the BlueCherry
 * IoT-connection.
 */

#ifndef SSH_H
#define	SSH_H

#include <stdbool.h>

#include "network.h"

/**
 * @brief This enumeration contains all actions to take on the child OpenSSH 
 * connection.
 */
enum ssh_control_action {
    SSH_CONTINUE = 0,
    SSH_RESTART,
    SSH_EXIT
};

void ssh_init();

void ssh_internet_wait();

void ssh_get_server(struct ssh_server *serv);

bool ssh_set_known_host(char *ip, int port, char *key);

void ssh_wait_for_active();

void ssh_prepare_keys();

void ssh_start_data_connection();

enum ssh_control_action ssh_watch();

enum ssh_control_action ssh_wait();

void ssh_kill();

void ssh_signal_handler(int sig);

void ssh_exit_with_error();

#endif

