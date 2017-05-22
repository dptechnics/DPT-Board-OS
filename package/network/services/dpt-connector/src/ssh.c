/**
 * @file ssh.c
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

#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <setjmp.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#include "ssh.h"
#include "config.h"
#include "log.h"
#include "network.h"
#include "device.h"
#include "keymanagement.h"
#include "ipc-status.h"

/**
 * @brief The SSH child connection PID.
 */
int con_pid;

/**
 * @brief This flag will be set to 1 when the child SSH connection must be restarted.
 */
volatile sig_atomic_t restart_ssh;

/**
 * @brief This flag will be set to when when a long jmp should be done
 */
volatile sig_atomic_t canlongjmp;

/**
 * @brief The buffer to save the current environment in when we do a longjump.
 */
sigjmp_buf jumpbuf;

/**
 * @brief This function initializes the SSH connection monitor.
 * 
 * This function will initialize the SSH connection monitor and prepare it
 * to start the child SSH connection to the BlueCherry IoT-platform.
 * 
 * @return None.
 */
void ssh_init() 
{
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
 * @brief This function blocks until the BlueCherry platform is available.
 * 
 * This function will active wait on the availability of the BlueCherry IoT
 * platform by continuously checking the connection.
 * 
 * @return None.
 */
void ssh_internet_wait() 
{
    while(!network_check_bluecherry_conn()) {
        log_event(LG_DEBUG, "The BlueCherry IoT platform service is not reachable, no internet?\n");
        sleep(1);
    }
    log_event(LG_INFO, "The BlueCherry IoT platform service is reachable\n");
}

/**
 * @brief This function blocks until the DPT-Connector can connect to the platform.
 * 
 * This function will block until the BlueCherry IoT platform returns a valid
 * SSH node.
 * 
 * @param serv The SSH node structure to write the connection info in.
 */
void ssh_get_server(struct ssh_server *serv) 
{
    
    while (true) {
        
        /* Request SSH node from the BlueCherry IoT platform until it works */
        if(network_request_ssh_server(serv)) {
            /* Set known hosts configuration */
            ssh_set_known_host(serv->ipv4, serv->serverport, serv->hostkey);
            return;
        } else {
            log_event(LG_DEBUG, "The BlueCherry platform is not assigning a node, not connecting\n");
        }

        /* Wait 5 seconds before retrying */
        sleep(5);
    }
}

/**
 * @brief Overwrite or create the known hosts file for a specific SSH node.
 * 
 * This function will overwrite an existing or create a new known hosts file 
 * and append the information needed to trust the given SSH node.
 * 
 * @param ip The IP of the remote host. 
 * @param port The port of the remote host. 
 * @param key The public SSH fingerprint of the host to trust.
 * 
 * @return True when the host key could be set.
 */
bool ssh_set_known_host(char *ip, int port, char *key)
{
    FILE* file = fopen("/root/.ssh/known_hosts", "w");
    if(file == NULL) {
        log_event(LG_ERROR, "Could not create or overwrite the known_hosts file\n");
        return false;
    }
    
    fprintf(file, "[%s]:%d %s\n", ip, port, key);
    fclose(file);
    
    return true;
}

/**
 * @brief This function will block until the BlueCherry connection flag is on.
 * 
 * This function reads the BlueCherry activation flag from the device flash and
 * blocks until this flag is active. 
 * 
 * @return None.
 */
void ssh_wait_for_active()
{
    while(true) {
        /* Check if the BlueCherry activation flag is set */
        if(device_get_bluecherry_active()) {        
            log_event(LG_DEBUG, "The BlueCherry activation flag is set, continue\n");
            return;
        } else {
            log_event(LG_DEBUG, "The BlueCherry activation flag is not set, blocking\n");
        }
        
        sleep(10);
    }
    
}

/**
 * @brief This function will block until the SSH keys are created and synced.
 * 
 * This function will try to load the SSH keys from the device flash and place
 * them in the file system with the correct permissions so the OpenSSH client 
 * can use them. When the keys are not present or corrupted a new pair of keys
 * will be generated and synchronized with the BlueCherry cloud. This function
 * will block as long as this process is not completed.
 * 
 * @return None.
 */
void ssh_prepare_keys() 
{   
    while(!keymanagement_check_and_load_keypair()) {
        log_event(LG_INFO, "No valid SSH keys could be read from flash, generating new ones.\n");
        
        while(!keymanagement_generate_and_store_keypair()) {
            log_event(LG_ERROR, "Generating SSH keys failed, retrying in 5 seconds\n");
            sleep(5);
        }

        while(!network_update_ssh_key()) {
            log_event(LG_ERROR, "Could not sync new SSH keys with BlueCherry, retrying in 5 seconds\n");
            sleep(5);
        }
    }
}


/**
 * @brief Start the BlueCherry IoT data connection.
 * 
 * This connection will start an SSH connection to the BlueCherry Internet-of-Things
 * platform and monitor the connection to make it 100% stable.
 * 
 * @return None.
 */
void ssh_start_data_connection() 
{
    char location[64] = {0};
    char rtunnel[32] = {0};
    char ssh_port[16] = {0};
    struct ssh_server serv;

    while (1) {
        restart_ssh = 0;
        
        /* Wait for the BlueCherry connection to be activated */
        ipc_status_set(IPC_STATUS_INACTIVE);
        ssh_wait_for_active();

        /* Wait for internet connection */
        ipc_status_set(IPC_STATUS_NO_NETWORK);
        ssh_internet_wait();
        
        /* Prepare the SSH key management */
        ipc_status_set(IPC_STATUS_GENERATING_KEYS);
        ssh_prepare_keys();

        /* Wait for SSH data port */
        ipc_status_set(IPC_STATUS_REQUESTING_PORTS);
        ssh_get_server(&serv);
        
        ipc_status_set(IPC_STATUS_CONNECTING);
        
        /* Read the type ID from flash */
        char dev_type_id[DEVICE_TYPE_ID_BUFF_LEN];
        if(!device_get_type_id(dev_type_id)) {
            log_event(LG_ERROR, "Could not read device type ID from flash\n");
            ssh_exit_with_error();
        }

        /* Read the device ID from flash */
        char dev_dev_id[DEVICE_ID_BUFF_LEN];
        if(!device_get_device_id(dev_dev_id)) {
            log_event(LG_ERROR, "Could not read device ID from flash\n");
            ssh_exit_with_error();
        }

        /* Format the connection arguments */
        snprintf(rtunnel, 32, "0.0.0.0:%d:localhost:80", serv.port);
        snprintf(location, 64, "%s.%s@%s", dev_type_id, dev_dev_id, serv.ipv4);
        snprintf(ssh_port, 16, "%d", serv.serverport);

        char* arg[] = {
            appconf->ssh_path,
            "-p", ssh_port,
            "-R", rtunnel,
            "-i", appconf->identity_file,
            "-N",
            "-o ServerAliveInterval 30",
            "-o ServerAliveCountMax 2",
            location,
            NULL
        };

        con_pid = fork();
        switch (con_pid) {
            case 0:
                log_event(LG_DEBUG, "Starting BlueCherry connection\n");

                /* Start SSH data connection */
                execv(arg[0], arg);

                /* Exit the fork process with an error */
                log_event(LG_ERROR, "BlueCherry connection failed with error: %s\n", strerror(errno));
                ssh_exit_with_error();

                /* If we don't do this the loop could restart */
                kill(SIGTERM, getppid());
                exit(1);
                break;
            case -1:
                con_pid = 0;
                log_event(LG_ERROR, "Could not fork parent process: %s\n", strerror(errno));
                ssh_exit_with_error();
                break;
            default:
                ipc_status_set(IPC_STATUS_CONNECTED);
                log_event(LG_INFO, "BlueCherry connection established with pid: %d\n", con_pid);
                if (ssh_watch() == SSH_EXIT)
                    return;
                break;
        }
    }
}

/**
 * @brief This function watches an OpenSSH connection for stability.
 * 
 * This function catches signals and exit codes from the child OpenSSH
 * connection and returns which action should be taken on a certain event.
 * 
 * @return The control action to take on the child OpenSSH connection.
 */
enum ssh_control_action ssh_watch() 
{
    int r;
    int val;
    int secs_left;

    while (true) {
        /* Check if we need to restart SSH */
        if (restart_ssh) {
            log_event(LG_INFO, "DPT-Connector will restart the BlueCherry connection\n");
            ssh_kill();
            return SSH_RESTART;
        }


        if ((val = sigsetjmp(jumpbuf, 1)) == 0) {
            log_event(LG_DEBUG, "Checking BlueCherry connection with PID: %d\n", con_pid);

            /* Wait for a signal from the child SSH connection */
            r = ssh_wait(WNOHANG);
            if (r != SSH_CONTINUE) {
                log_event(LG_DEBUG, "The BlueCherry connection is no longer working, taking action: %d\n", r);
                return r;
            }

            /* Reset all alarms for DPT-Connector and reset them */
            secs_left = alarm(0);
            if (secs_left == 0)
                secs_left = CONFIG_SSH_CONN_POLL_TIME;
            alarm(secs_left);

            log_event(LG_DEBUG, "New SSH connection check in %d seconds", secs_left);

            /* Wait for the alarm */
            canlongjmp = 1;
            pause();
        } else {
            switch (val) {
                case SIGINT:
                case SIGTERM:
                case SIGQUIT:
                case SIGABRT:
                    log_event(LG_INFO, "DPT-Connector received signal to exit (%d)", val);
                    ssh_kill();
                    return SSH_EXIT;
                    break;
                case SIGALRM:
                default:
                    break;
            }
        }
    }
}

/**
 * @brief This function blocks until the child OpenSSH process changes state.
 * 
 * Wait for the OpenSSH child process to change state. This function
 * returns immediately when the child process did not exit. 
 * 
 * @return The control action to take on the child OpenSSH connection.
 */
enum ssh_control_action ssh_wait() 
{
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
                    log_event(LG_INFO, "OpenSSH exited on signal %d, DPT-Connector will also exit\n", WTERMSIG(status));
                    return SSH_EXIT;
                    break;
                default:
                    /* Restart on any other signal */
                    log_event(LG_INFO, "OpenSSH exited on signal %d, restarting the BlueCherry connection\n", WTERMSIG(status));
                    return SSH_RESTART;
                    break;
            }
        } else if (WIFEXITED(status)) {
            evalue = WEXITSTATUS(status);

            switch (evalue) {
                case 255:
                case 1:
                    log_event(LG_INFO, "OpenSSH exited with error status %d, restarting the BlueCherry connection\n", evalue);
                    return SSH_RESTART;
                case 0:
                default:
                    log_event(LG_ERROR, "OpenSSH exited with status %d, DPT-Connector is exiting\n", evalue);
                    return SSH_EXIT;
                    break;
            }
        }
    }

    /* Continue monitoring */
    return SSH_CONTINUE;
}

/**
 * @brief This function kills the child OpenSSH connection.
 * 
 * This function kills the OpenSSH child connection by sending the SIGTERM
 * signal to it's PID.
 * 
 * @return None.
 */
void ssh_kill() 
{
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
            log_event(LG_ERROR, "Could not kill the BlueCherry connection: %s\n", strerror(errno));
        }
    }
}

/**
 * @brief The application's signal handler.
 * 
 * This function handles signals from other programs. 
 * 
 * @param sig The number of the signal. 
 * 
 * @return None.
 */
void ssh_signal_handler(int sig) 
{
    if (canlongjmp) {
        canlongjmp = 0;
        siglongjmp(jumpbuf, sig);
    }
}

/**
 * @brief Exit the DPT-Connector with an error.
 * 
 * This function will end the child OpenSSH connection and exit
 * with status code 1.
 * 
 * @return None.
 */
void ssh_exit_with_error() 
{
    ssh_kill();
    _exit(1);
}
