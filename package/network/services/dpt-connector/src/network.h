/**
 * @file network.h
 * @author Daan Pape <daan@dptechnics.com>
 * @date 4 Nov 2014
 * @copyright DPTechnics
 * @brief DPT-connector IoT-connector network functions
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
 * This file contains all the network functions for the DPTechnics BlueCherry
 * Internet-of-Things connector.
 */

#ifndef DPTNETWORK_H
#define	DPTNETWORK_H

#include <stdint.h>
#include <stdbool.h>
#include <netinet/in.h>

/**
 * @defgroup NETWORK Constants which describe network functions.
 * @{
 */

/**
 * @brief The length of the server host key.
 */
#define NETWORK_SERVER_HKEY_LEN      512

/** @}*/

/**
 * @brief This structure represents a BlueCherry platform SSH endpoint.
 */
struct ssh_server {
    int port;                               /**< Port to reverse tunnel to */
    char ipv4[INET_ADDRSTRLEN];             /**< IPv4 address of SSH node */
    char ipv6[INET6_ADDRSTRLEN];            /**< IPv6 address of SSH node */
    int serverport;                         /**< SSH listening port of SSH node */
    char hostkey[NETWORK_SERVER_HKEY_LEN];  /**< Hostkey of the SSH node */
};

bool network_request_ssh_server(struct ssh_server *serv);

bool network_check_bluecherry_conn();

bool network_update_ssh_key();

#endif

