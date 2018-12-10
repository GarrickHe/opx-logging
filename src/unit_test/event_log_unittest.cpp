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
 * filename: event_log_unittest.cpp
 */

#include "event_log.h"
#include "gtest/gtest.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

bool event_log_change_status_test(){

    EV_LOG_TRACE(ev_log_t_NPU,ev_log_s_WARNING,"ID","Error occured.. %d %s",0,"Cliff");

    event_logging_set_enabled_flag("ev_log_t_NPU",EV_T_LOG_DEBUG,false);
    EV_LOG_TRACE(ev_log_t_NPU,ev_log_s_WARNING,"ID","Error occured..%d %s",1,"2");
    EV_LOG_TRACE(ev_log_t_NPU,ev_log_s_MINOR,"ID","Error occured..%d %s",1,"Viraj");
    EV_LOG_INFO(ev_log_t_NPU,ev_log_s_WARNING,"ID","Error occured..%d %s",1,"2");
    EV_LOG_INFO(ev_log_t_NPU,ev_log_s_MAJOR,"ID","Error occured..%d %s",1,"Viraj");
    EV_LOG(INFO,NPU,0,"ID","Error occured..%d %s",1,"Viraj2");

    event_logging_set_enabled_flag("ev_log_t_NPU",EV_T_LOG_DEBUG,true);
    kill(getpid(),SIGUSR1);
    EV_LOG_ERR(ev_log_t_NPU,ev_log_s_MINOR,"ID","Error occured..%d %s",1,"2");
    EV_LOGGING(NAS_L2,EMERG,"EMERG","Error occured..%d %s",1,"2");
    EV_LOGGING(NAS_L2,ALERT,"ALERT","Error occured..%d %s",1,"2");
    EV_LOGGING(NAS_L2,CRIT,"CRIT","Error occured..%d %s",1,"2");
    EV_LOGGING(NAS_L2,ERR,"ERR","Error occured..%d %s",1,"2");
    EV_LOGGING(NAS_L2,WARNING,"WARNING","Error occured..%d %s",1,"2");
    EV_LOGGING(NAS_L2,NOTICE,"NOTICE","Error occured..%d %s",1,"2");
    EV_LOGGING(NAS_L2,INFO,"INFO","Error occured..%d %s",1,"2");
    EV_LOGGING(NAS_L2,DEBUG,"DEBUG","Error occured..%d %s",1,"2");
    struct stat sb;
    int rc = stat("/noname/notexist",&sb);
    if (rc!=0) {
        EV_LOG_ERRNO(ev_log_t_NPU,ev_log_s_MINOR,"Minor",errno);
    }
    return true;
}


TEST(event_log_test,event_log_change_status) {
    ASSERT_TRUE(event_log_change_status_test());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
