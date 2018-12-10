/*
 * Copyright (c) 2018 Dell Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * THIS CODE IS PROVIDED ON AN *AS IS* BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 * FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 * See the Apache Version 2.0 License for specific language governing
 * permissions and limitations under the License.
 */

/*
 * filename: event_log.h
 */

#ifndef __EVENT_LOG_H
#define __EVENT_LOG_H

#include "event_log_types.h"

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>



#ifdef __cplusplus
extern "C" {
#endif


/*Convert the module name to a string*/
#define _EV_LOG_TO_STRING(x) #x

/**
 * @brief log the msg
 *
 * @param MOD a module from event_log_types.h
 * @param LVL a syslog level to be used for logging from event_log_types.h
 * @param ID  a event id (private id for trace logs)
 * @param msg the message and parameters will follow this data
 */
#define EV_LOGGING(MOD,LVL,ID,msg, ...) \
    (void)((event_logging_is_enabled(_EV_LOG_TO_STRING(MOD), EV_T_LOG_ ## LVL)) && \
        ((EV_T_LOG_ ## LVL != EV_T_LOG_DEBUG) ?    \
            event_log_msg(_EV_LOG_TO_STRING(MOD),EV_T_LOG_ ## LVL, 0, "CODE_FILE=" __FILE__,\
                "CODE_LINE=" _EV_LOG_TO_STRING(__LINE__),__func__,ID,0,"[%s:%s], " msg,_EV_LOG_TO_STRING(MOD),ID,##__VA_ARGS__):    \
            event_log_msg(_EV_LOG_TO_STRING(MOD),EV_T_LOG_ ## LVL, 0, "CODE_FILE=" __FILE__,\
                "CODE_LINE=" _EV_LOG_TO_STRING(__LINE__),__func__,ID,0,"[%s:%s] %s:%s:%d, " msg,_EV_LOG_TO_STRING(MOD),ID,\
                __FILE__,__func__,__LINE__,##__VA_ARGS__)))

/**
 * @brief change all logging state (enable or disable)
 *
 * @param state is to enable (true) or disable (false) all logging state
 *
 */
void event_log_change_all_state(bool state);

/**
 * @brief checks if logging is enabled for a given module and log-level
 *
 * @param mod is a string tag for the module
 * @param loglvl is the numeric log-level from event_log_types.h
 * @return current logging status for given parameters (true/false)
 */
bool event_logging_is_enabled(const char *mod,size_t loglvl);


/**
 * @brief     Set the state of the module's log level.  By default, all trace logs
 *             are disabled
 * @param mod is a string tag for the module
 * @param loglvl is the numeric log-level from event_log_types.h
 * @return current logging status for given parameters (true/false)
 */
void event_logging_set_enabled_flag(const char *mod,size_t loglvl, bool how);

/**
 * @brief The following function will send the log to the appropriate backend
 *         logging system.  This is not meant to be directly called by applications
 *         the logging macros should be used as a front end
 *
 * @param module is a string tag
 * @param level is the numeric log-level from event_log_types.h
 * @param ident is a numeric id if provided
 * @param file is the filename
 * @param ln is the line number of the entry
 * @param fun is the function call name
 * @param tag is a string that can identify the issue or otherwise qualify the log message
 * @param err is the error number
 * @param msg is the message which needs to be logged
 *
 */
bool event_log_msg(const char *module, int level, int ident, const char *file,
        const char * ln, const char *fun, const char *tag, int err, const char *msg,...);

/**
 * @brief - load the latest logging configuration after it has been changed
 *
 * Loading of the latest logging configuration is already handled when user
 * send the SIGUP signal to the process. This API can be used if some third
 * party applications are handling the SIGHUP signal and in this case new logging
 * configuration needs to be loaded at run time.
 *
 */

void event_log_reload_config(void);

#include "event_log_dep.h"

#ifdef __cplusplus
}
#endif

#endif
