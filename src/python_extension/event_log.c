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

#include <python2.7/Python.h>

#include "event_log.h"

extern int event_log_name_to_mod(const char *name, int len);

static PyObject *__all_logs(int log_level, PyObject *self, PyObject *args)
{
    int        lvl, lineno;
    const char *modname, *tag, *filename, *func, *msg;

    if (!PyArg_ParseTuple(args, "sisssis", &modname, &lvl, &tag, &filename, &func, &lineno, &msg))  return (NULL);

    if (event_logging_is_enabled(modname, lvl)) {
        char _ln[100];
        char _file[512];
        snprintf(_ln,sizeof(_ln)-1,"CODE_LINE=%d",(int)lineno);
        snprintf(_file,sizeof(_file)-1,"CODE_FILE=%s",filename);
        event_log_msg(modname, lvl, 0,_file,_ln,func,tag,0,msg);
    }

    return (Py_BuildValue(""));
}


static PyObject *
log_trace(PyObject *self, PyObject *args)
{
    return __all_logs(EV_T_LOG_DEBUG,self,args);
}

static PyObject *
log_info(PyObject *self, PyObject *args)
{
    return __all_logs(EV_T_LOG_INFO,self,args);
}

static PyObject *
log_err(PyObject *self, PyObject *args)
{
    return __all_logs(EV_T_LOG_ERR,self,args);
}

static PyObject * logging(PyObject *self, PyObject *args)
{
    return __all_logs(EV_T_LOG_INFO,self,args);
}

static PyMethodDef methods[] = {
    { "log_trace", log_trace, METH_VARARGS, "Log trace" },
    { "log_info",  log_info,  METH_VARARGS, "Log info" },
    { "log_err",   log_err,   METH_VARARGS, "Log error" },
    { "logging",   logging,   METH_VARARGS, "Log msg" },
    { NULL, NULL, 0, NULL }        /* Sentinel */
};

PyMODINIT_FUNC
initevent_log(void)
{
    PyObject *m = Py_InitModule("event_log", methods);

    PyModule_AddIntConstant(m, "EMERG", EV_T_LOG_EMERG);
    PyModule_AddIntConstant(m, "ALERT", EV_T_LOG_ALERT);
    PyModule_AddIntConstant(m, "CRIT", EV_T_LOG_CRIT);
    PyModule_AddIntConstant(m, "ERR", EV_T_LOG_ERR);
    PyModule_AddIntConstant(m, "WARNING", EV_T_LOG_WARNING);
    PyModule_AddIntConstant(m, "NOTICE", EV_T_LOG_NOTICE);
    PyModule_AddIntConstant(m, "INFO", EV_T_LOG_INFO);
    PyModule_AddIntConstant(m, "DEBUG", EV_T_LOG_DEBUG);}
