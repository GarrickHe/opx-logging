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
 * filename: event_log_types.h
 */

#ifndef __EVENT_LOG_TYPES_H
#define __EVENT_LOG_TYPES_H

#include <syslog.h>

#define EV_T_LOG_EMERG LOG_EMERG
#define EV_T_LOG_ALERT LOG_ALERT
#define EV_T_LOG_CRIT LOG_CRIT
#define EV_T_LOG_ERR LOG_ERR
#define EV_T_LOG_WARNING LOG_WARNING
#define EV_T_LOG_NOTICE LOG_NOTICE
#define EV_T_LOG_INFO LOG_INFO
#define EV_T_LOG_DEBUG LOG_DEBUG
#define EV_T_LOG_TRACE LOG_DEBUG

#define DEFAULT_LOG_LEVEL EV_T_LOG_NOTICE

//  Used in the script for automation if new log level added please update it accordingly.
#define MAX_LOG_LEVEL 7

//  Used to identify special  logs
enum ev_log_e {
    ev_log_trace,
    ev_log_alarm,
    ev_log_debug,
    ev_log_event,
    ev_log_audit
};

#
/* Audit log facility */
#define EV_T_LOG_AUDIT (13<<3)

/* Default trace facility */
#define DEFAULT_TRACE_FACILITY LOG_LOCAL7

//   Enums are used as index, so be careful when adding a new sublevel, only increment by one
enum e_log_sublevel {
    ev_log_s_CRITICAL=0,
    ev_log_s_MAJOR=1,
    ev_log_s_MINOR=2,
    ev_log_s_WARNING=3,
    ev_log_s_MAX,    //add all items above this line
};

#include "event_log_dep.h"

#endif
