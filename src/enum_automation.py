#!/usr/bin/python
#
# Copyright (c) 2015 Dell Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License. You may obtain
# a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
#
# THIS CODE IS PROVIDED ON AN *AS IS* BASIS, WITHOUT WARRANTIES OR
# CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
# LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
# FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
#
# See the Apache Version 2.0 License for specific language governing
# permissions and limitations under the License.
#

import sys
import subprocess
import string
import os

def usage():
    print "gen_hdr.py [input_c_file][op_src_file]"
    sys.exit()

def generate_header():

    if len(sys.argv) < 4:
        usage()

    ip_file = sys.argv[1]
    hdr_file = sys.argv[2]
    src_file = sys.argv[3]

    sys_list = {}
    lvl_list = {}
    sublvl_list = {}
    max_lvl = 0

    src = open(src_file,"w")
    enum_list = (subprocess.check_output("ctags -x --c-types=e "+ip_file+" | cut -f1 -d ''", shell=True)).split("\n")
    def_list = (subprocess.check_output("ctags -x --c-types=d "+ip_file+" | cut -f1 -d ''", shell=True)).split("\n")
    for enum_line in enum_list:
        enum_array= enum_line.split(" ")
        if enum_array[0]:
            if "ev_log_t" in enum_array[0]:
                if "=" in enum_array[len(enum_array)-1]:
                    sys_list[int(enum_array[len(enum_array)-1].split("=")[1].split(",")[0])]=enum_array[0]
            elif "ev_log_s" in enum_array[0]:
                if "=" in enum_array[len(enum_array)-1]:
                    sublvl_list[int(enum_array[len(enum_array)-1].split("=")[1].split(",")[0])]=enum_array[0]
    for def_line in def_list:
        def_array= def_line.split()
        if def_array:
            lvl_list[int(def_array[2])]=def_array[0]
            if "MAX" in def_array[0]:
                max_lvl = int(def_array[len(def_array)-1])
    ifdef_str = "_".join(hdr_file.split("."))
    ifdef_str = "__" + ifdef_str.upper()
    ifdef_str = ifdef_str.split("/")[-1]

    src.write("""
/*
 * filename: event_log_levels.c
 * (c) Copyright 2014 Dell Inc. All Rights Reserved.
 *
 * This is an auto-generated file. Any changes made to evennt_log_types.h will regenerate the new
 * contents for this file. This file is generated by enum_automation.py script
 *
 */

#include """+"\""+hdr_file.split("/")[-1]+"\""+"""
#include "event_log_types.h"
#include <stdlib.h>

static sys_log_status_t event_log_default_state[ ] =
""")

    sys_list_str =""
    sys_map_str = "{ "
    for sys_item in sorted(sys_list):
        sys_list_str += sys_list[sys_item]+","
        sys_map_str += str(sys_item)+":\""+sys_list[sys_item].split("_")[-1]+"\", "
    sys_map_str += "} "

    sublvl_str_true = "{  true , true , true , true }"
    sublvl_str_false = "{  false , false , false , false }"
    sublvl_str_info = "{  true , false , false , false }"

    lvl_str = "{ \n"
    for lvl in range(0,max_lvl+1):
        #Log levels ERR and higher are enabled by default
        if lvl <= 3 :
            lvl_str += "\t\t{ "+sublvl_str_true+" },\n"
        elif lvl == 6 :
            lvl_str += "\t\t{ "+sublvl_str_info+" },\n"
        else:
            lvl_str += "\t\t{ "+sublvl_str_false+" },\n"
    lvl_str += "\t}"

    logging_lvl_str = "DEFAULT_LOG_LEVEL"

    ix = 0
    sys_str = "{ \n"
    sys_str += " // logging state for module " + sys_list[ix] +" \n"
    sys_str += "\t// log-level values for ERR, DBG and INFO \n"
    sys_str += "\t\t\t// log sub-level values CRITICAL,MAJOR,MINOR,WARNING\n"
    ix +=1
    for sys_item in range(0,len(sys_list)):
        if ix == 1:
            sys_str += "\t{ "+lvl_str+" },\n"
        elif ix == len(sys_list):
            break
        else:
            sys_str += "\t // logging state for module " + sys_list[ix] +" \n { "+lvl_str+" },\n"
        ix += 1
    sys_str += "} ; "
    src.write(sys_str +"""

static log_level_t event_logging_default_state[ ] =

""")

    ix = 0
    sys_str = "{ \n"
    sys_str += " // logging state for module " + sys_list[ix] +" \n"
    sys_str += "// log-level values \n"
    ix +=1
    for sys_item in range(0,len(sys_list)):
        if ix == 1:
            sys_str += "\t "+logging_lvl_str+" ,\n"
        elif ix == len(sys_list):
            break
        else:
            sys_str += "\t // logging state for module " + sys_list[ix] +" \n  "+logging_lvl_str+" ,\n"
        ix += 1
    sys_str += "} ; "

    src.write(sys_str +"""

const char * sys_enum_to_str [] = {
""")
    for key in sorted(sys_list):
        src.write("\""+"_".join(sys_list[key].split("_")[3:])+"\",\n")
    src.write("""};

const char * sublvl_enum_to_str [] = {
""")
    sublvl_convert_str = ""
    for key in sorted(sublvl_list):
        src.write("\""+sublvl_list[key].split("_")[-1]+"\",\n")
    src.write("""};

const char * lvl_enum_to_str [] = {
"EMERG",
"ALERT",
"CRIT",
"ERR",
"WARNING",
"NOTICE",
"INFO",
"DEBUG",
};

sys_log_status_t * event_log_get_default_state() {
    return &(event_log_default_state[0]);
}

int event_log_get_default_state_size() {
    return sizeof(event_log_default_state);
}

const char * event_log_mod_to_name(int id) {
    return sys_enum_to_str[id];
}

const char * event_log_sublvl_to_name(int id) {
        return sublvl_enum_to_str[id];
}

const char * event_log_lvl_to_name(int id) {
        return lvl_enum_to_str[id];
}

log_level_t * event_logging_get_default_state() {
    return &(event_logging_default_state[0]);
}

unsigned int event_logging_get_default_state_size() {
    return sizeof(event_logging_default_state);
}
""");
    src.close()


def main():
    generate_header()

if __name__ == '__main__':
    main()
