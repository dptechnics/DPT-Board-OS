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
 * File: dptnetwork.h
 * Created on November 4, 2014, 10:41 PM
 */

#ifndef DPTNETWORK_H
#define	DPTNETWORK_H

#include <stdint.h>
#include <stdbool.h>
#include <netinet/in.h>

#define DPTNET_SERVER_HKEY_LEN      512

/**
 * An SSH server to connect to
 */
typedef struct {
        int port;                           /* Port to reverse tunnel to */
    char ipv4[INET_ADDRSTRLEN];             /* IPv4 address of SSH node */
    char ipv6[INET6_ADDRSTRLEN];            /* IPv6 address of SSH node */
    int serverport;                         /* SSH listening port of SSH node */
    char hostkey[DPTNET_SERVER_HKEY_LEN];   /* Hostkey of the SSH node */
} ssh_server;

/*
 * Memory structure to save HTTP responses in. 
 */
struct curl_mem_struct {
  char *memory;
  size_t size;
};

/**
 * Request an SSH server node to connect to. 
 * @param serv structure to fill up on success. 
 * @return true on success, false on error. 
 */
bool dptnet_request_ssh_server(ssh_server* serv);

/**
 * Returns true when the board can reach the BlueCherry server
 * @return true when there is a connection
 */

/**
 * Returns true when the DPT-Connector can reach
 * the BlueCherry platform. 
 * @return true when the BlueCherry platform is reachable. 
 */
bool dptnet_check_bluecherry_conn();

#endif

