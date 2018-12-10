#
# Copyright (c) 2018 Dell Inc.
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

ACLOCAL_AMFLAGS=-I m4

SUBDIRS = inc

#Script files
bin_SCRIPTS = src/opx_logging_cli

#The logging library
lib_LTLIBRARIES = libopx_logging.la

libopx_logging_la_SOURCES = src/event_log.cpp

libopx_logging_la_LDFLAGS = -lxml2 -lpthread -lrt -version-info 1:1:0 -lsystemd

libopx_logging_la_CFLAGS = -I$(top_srcdir)/inc/opx -I$(includedir)/libxml2
libopx_logging_la_CPPFLAGS = -I$(top_srcdir)/inc/opx -I$(includedir)/libxml2 -I$(includedir) -std=c++11


utdir = /usr/bin/tests
#ut_PROGRAMS = event_log_unittest
#event_log_unittest_SOURCES = src/unit_test/event_log_unittest.cpp
#event_log_unittest_CPPFLAGS = -I$(top_srcdir)/opx
#event_log_unittest_LDFLAGS = -lgtest -lgtest_main -lpthread

#logging module
pyexec_LTLIBRARIES = event_log.la
event_log_la_LDFLAGS = -module -avoid-version
event_log_la_SOURCES = src/python_extension/event_log.c
event_log_la_CPPFLAGS=-I$(top_srcdir)/src/python_extension -I$(top_srcdir)/inc/opx -I$(includedir)/opx -I$(includedir)/python2.7
event_log_la_LIBADD=libopx_logging.la -lpython2.7
