/**
 * @file log.c
 * @author Daan Pape <daan@dptechnics.com>
 * @date 6 Mar 2016
 * @copyright DPTechnics
 * @brief DPT-connector daemon logger module
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
 * This file contains the implementation of the log module.
 */

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <syslog.h>

#include "log.h"
#include "config.h"

/**
 * @brief Internal array with logging formats.
 * 
 * This array maps the @ref log_level enumeration to the associated format
 * string.
 */
const char* const _log_formats[] = {
    "",
    "[ERROR][%d-%d-%d %d:%d:%d] ",
    "[WARNING][%d-%d-%d %d:%d:%d] ",
    "[INFO][%d-%d-%d %d:%d:%d] ",
    "[DEBUG][%d-%d-%d %d:%d:%d] "
};

/**
 * @brief Log to a file without checking configuration.
 * 
 * This function will log an entry without checking any configuration. This means
 * the entry will always be written if the file is accessible.
 * 
 * @param stream The file stream to write the log entry to.
 * @param level The logging level of the this log entry.
 * @param format the format string of this entry in printf style.
 * @param ... the arguments to log.
 * 
 * @return None
 */
void log_basic(FILE *stream, enum log_level level, const char *format, ...) {    
    /* Get the localized time */
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    /* Print the log with varargs */
    va_list args;
    va_start(args, format);
    fprintf(stream, _log_formats[level], tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    vfprintf(stream, format, args);
    va_end(args);
}


/**
 * @brief Log an event to the configured logging file/stream.
 * 
 * This function will log an entry to the destination as configured in the application
 * wide configuration. When the log level of the entry has a lower priority of the 
 * configured level the entry will be discarded. This function can only be called after
 * the configuration has been loaded successfully.
 * 
 * @param level The logging level of the this log entry.
 * @param format the format string of this entry in printf style.
 * @param ... the arguments to log.
 * 
 * @return None
 */
void log_event(enum log_level level, const char *format, ...)
{
    if(level > appconf->loglevel) {
        /* Return as quickly as possible if logging is not needed */
        return;
    }
    
    /* Get the localized time */
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    /* Open the variable argument list */
    va_list args;
    va_start(args, format);
    
    if(appconf->log_to_syslog) {
        switch(level) {
            case LG_DEBUG:
                vsyslog(LOG_DEBUG, format, args);
                break;
            case LG_ERROR:
                vsyslog(LOG_ERR, format, args);
                break;
            case LG_INFO:
                vsyslog(LOG_INFO, format, args);
                break;
            case LG_WARNING:
                vsyslog(LOG_WARNING, format, args);
                break;   
            default:
                break;
        }
    } else {
        /* Print the log with varargs */ 
        fprintf(appconf->logfile, _log_formats[level], tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        vfprintf(appconf->logfile, format, args);
    }
    
    /* Close the variable argument list */
    va_end(args);
}