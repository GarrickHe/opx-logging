© 2018 OpenSwitch project. All information is contributed to and made available by OPX under the Creative Commons Attribution 4.0 International License (available at http://creativecommons.org/licenses/by/4.0/).

# opx-logging
This repository contains logging utilities for the OPX project which provide a simple wrapper for syslog activities. These wrapper functions and macros add the line number of the calling code, as well as other additional pieces of information.

You can optionally use the CLI for run-time modification of logging levels called _opx_logging_cli_.

All headers are located in OPX, and will be installed in the _*/usr/include/opx*_ folder (based on your prefix).

## Packages
- libopx-logging1\_*version*\_*arch*.deb — Utility libraries  
- libopx-logging-dev\_*version*\_*arch*.deb — Exported header files
- python-opx-logging\_*version*\_*arch*.deb — Python bindings

See [Architecture](https://github.com/open-switch/opx-docs/wiki/Architecture) for more information on the Logging module.

(c) 2018 Dell Inc. or its subsidiaries. All Rights Reserved.
