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

#ifndef LOGGING_INC_EVENT_LOG_DEP_H_
#define LOGGING_INC_EVENT_LOG_DEP_H_


/**
 * @deprecated THIS API HAS BEEN DEPRECATED, PLEASE DO NOT USE THIS
 *
 * @note Please use @sa EV_LOGGING API instead
 *
 * @brief trace a message to through syslog
 *
 * @param MOD a module from event_log_types.h
 * @param a logging level (0-3)
 * @param a event id (private id for trace logs
 * @param message a message (printf formatted.. no return char please)
 * @param parameters for the message in standard printf format
 */

#define EV_LOG_TRACE(MOD, LVL, ID, message, ... ) \
        EV_LOGGING(MOD,DEBUG,ID,message,  ## __VA_ARGS__)

/**
 * @deprecated THIS API HAS BEEN DEPRECATED, PLEASE DO NOT USE THIS
 *
 * @note Please use @sa EV_LOGGING API instead
 *
 * @brief log an error event.  may generate traps or the like...
 *
 * @param MOD a module from event_log_types.h
 * @param a event id (private id for trace logs
 * @param message a message (printf formatted.. no return char please)
 * @param parameters for the message in standard printf format
 */
#define EV_LOG_ERR(MOD, LVL, ID, message, ... ) \
    EV_LOGGING(MOD,ERR,ID,message, ##__VA_ARGS__)

/**
 * @deprecated THIS API HAS BEEN DEPRECATED, PLEASE DO NOT USE THIS
 *
 * @note Please use @sa EV_LOGGING API instead
 *
 * @brief info message
 *
 * @param MOD a module from event_log_types.h
 * @param a event id (private id for trace logs
 * @param message a message (printf formatted.. no return char please)
 * @param parameters for the message in standard printf format
 */
#define EV_LOG_INFO(MOD, LVL, ID, message, ... ) \
    EV_LOGGING(MOD,INFO,ID,message, ##__VA_ARGS__)

/**
 * @deprecated THIS API HAS BEEN DEPRECATED, PLEASE DO NOT USE THIS
 *
 * @note Please use @sa EV_LOGGING API instead
 *
 * @brief This is a wrapper for all of the above macros that will simplify the calling
 * @param what can be INFO, TRACE, ERR, DEBUG, CON_TRACE
 * @param MOD is the module concatenated with ev_log_t_ to create the real subsystem
 * @param LVL is a numeric level from 0-100 that indicates severity.  For error logs
 *             not applied at this point
 * @param ID a tag that is added to the log (can be used as classifier)
 * @param msg the message and parameters will follow this data
 */
#define EV_LOG( what, MOD, LVL, ID, msg, ...) \
    EV_LOGGING(MOD,what,ID,msg, ##__VA_ARGS__)

/**
 * @deprecated THIS API HAS BEEN DEPRECATED, PLEASE DO NOT USE THIS
 *
 * @note Please use @sa EV_LOGGING API instead
 *
 * @brief log the errno to the error log
 *
 * @param MOD a module from event_log_types.h
 * @param a event id (private id for trace logs
 * @param ERRNO is the errno that you want printed to the log
 */
#define EV_LOG_ERRNO(MOD, LVL, ID, ERRNO) \
    EV_LOGGING(MOD,ERR,ID,"Error occured %d",ERRNO)


/**
 * @deprecated THIS list of logging levels has been depreciated - do not use
 *
*/
//  Enums are used as index, so be careful when adding a new module, only increment by one
enum e_event_log_types_enums {
    ev_log_t_NULL=0,
    ev_log_t_NPU=1,
    ev_log_t_BOARD=2,
    ev_log_t_SYSTEM=3,
    ev_log_t_QOS=4,
    ev_log_t_COM=5,
    ev_log_t_INTERFACE=6,
    ev_log_t_NETLINK=7,
    ev_log_t_ROUTE=8,
    ev_log_t_ACL=9,
    ev_log_t_SFP=10,
    ev_log_t_MGMT=11,
    ev_log_t_DSAPI=12,
    ev_log_t_DB_SQL=13,
    ev_log_t_NDI=14,
    ev_log_t_SAI_FDB=15,
    ev_log_t_SAI_VLAN=16,
    ev_log_t_SAI_PORT=17,
    ev_log_t_SAI_SWITCH=18,
    ev_log_t_SAI_ROUTER=19,
    ev_log_t_SAI_ROUTER_INTF=20,
    ev_log_t_SAI_NEIGHBOR=21,
    ev_log_t_SAI_NEXT_HOP=22,
    ev_log_t_SAI_NEXT_HOP_GROUP=23,
    ev_log_t_SAI_ROUTE=24,
    ev_log_t_SAI_MIRROR=25,
    ev_log_t_NAS_L2=26,
    ev_log_t_NAS_COM=27,
    ev_log_t_FWD_SVCS_POLICY=28,
    ev_log_t_FWD_SVCS_QOS=29,
    ev_log_t_FWD_SVCS_NETMON=30,
    ev_log_t_SAI_LAG=31,
    ev_log_t_LACP=32,
    ev_log_t_XSTP=33,
    ev_log_t_LLDP=34,
    ev_log_t_DOT1X=35,
    ev_log_t_L2MAC=36,
    ev_log_t_L2CMN=37,
    ev_log_t_NAS_OS=38,
    ev_log_t_SAI_STP=39,
    ev_log_t_BGP=40,
    ev_log_t_OSPFV2=41,
    ev_log_t_OSPFV3=42,
    ev_log_t_RTM=43,
    ev_log_t_L3CMN=44,
    ev_log_t_PALD=45,
    ev_log_t_PAS_MONITOR=46,
    ev_log_t_PAS=47,
    ev_log_t_PAS_FUSE=48,
    ev_log_t_PAS_TIMER=49,
    ev_log_t_SAI_SAMPLEPACKET=50,
    ev_log_t_ENV_TMPCTL=51,
    ev_log_t_SWUPDATE=52,
    ev_log_t_INFRA_ALM=53,
    ev_log_t_INFRA_CHM=54,
    ev_log_t_INFRA_ETL=55,
    ev_log_t_INFRA_IFM=56,
    ev_log_t_INFRA_ISSU=57,
    ev_log_t_INFRA_PM=58,
    ev_log_t_SAI_HOSTIF=59,
    ev_log_t_SAI_QUEUE=60,
    ev_log_t_SAI_MAPS=61,
    ev_log_t_SAI_POLICER=62,
    ev_log_t_SAI_WRED=63,
    ev_log_t_SAI_SCHEDULER=64,
    ev_log_t_SAI_SCHEDULER_GRP=65,
    ev_log_t_SAI_QOS=66,
    ev_log_t_SERV_HW=67,
    ev_log_t_DATASTORE=68,
    ev_log_t_L3_SERVICES=69,
    ev_log_t_IPM=70,
    ev_log_t_MGMT_INTF=71,
    ev_log_t_L2_SERVICES=72,
    ev_log_t_FWD_SVCS_SFLOW=73,
    ev_log_t_INFRA_PPM=74,
    ev_log_t_SVC_SUPPORTASSIST=75,
    ev_log_t_INFRA_NDM=76,
    ev_log_t_INFRA_EQM=77,
    ev_log_t_SAI_UDF=78,
    ev_log_t_SAI_BUFFERS=79,
    ev_log_t_SWITCH_RES_MGR=80,
    ev_log_t_SERV_SW=81,
    ev_log_t_INFRA_NDS=82,
    ev_log_t_APP_VLT=83,
    ev_log_t_SUPPORT_BUNDLE=84,
    ev_log_t_APP_OPENFLOW=85,
    ev_log_t_SAI_HASH=86,
    ev_log_t_AFS_UTILS=87,
    ev_log_t_VRRP=88,
    ev_log_t_OTM=89,
    ev_log_t_INFRA_AFS=90,
    ev_log_t_INFRA_COMMON=91,
    ev_log_t_SAI_TUNNEL=92,
    ev_log_t_SERV_TRIGG=93,
    ev_log_t_APP_LADF=94,
    ev_log_t_ISCSI_OPT=95,
    ev_log_t_DCBX=96,
    ev_log_t_NBR_MGR=97,
    ev_log_t_FABRIC_AGENT=98,
    ev_log_t_DNV_APPS=99,
    ev_log_t_APP_FC=100,
    ev_log_t_SAI_FC=101,
    ev_log_t_MAX                ///add all items above this line
};



#endif /* LOGGING_INC_EVENT_LOG_DEP_H_ */
