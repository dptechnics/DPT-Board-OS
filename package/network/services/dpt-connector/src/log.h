/**
 * @file log.h
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
 * This file contains all the public log module functions and constants.
 */

#ifndef LOG_H
#define	LOG_H

#include <stdio.h>

/**
 * @brief The level to log a message with.
 * 
 * This enum represents the different log levels in the application. 
 */
enum log_level {
    LG_NONE = 0,   /**< Do not log anything */
    LG_ERROR,      /**< Only log application errors */
    LG_WARNING,    /**< Log warnings and errors */
    LG_INFO,       /**< Log info, warnings and errors */
    LG_DEBUG       /**< Print all logging information */ 
};

void log_basic(FILE *stream, enum log_level level, const char *format, ...);

void log_event(enum log_level level, const char *format, ...);

#endif