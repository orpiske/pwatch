/**
 Copyright 2015 Otavio Rodolfo Piske
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

#include "options.h"
#include "messenger.h"
#include "sigutil.h"


#if defined LINUX_BUILD

# include <linux/version.h>

# if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 4, 0)
#   define PTRACE_ATTACH_MODE PTRACE_SEIZE
# else 
#    define PTRACE_ATTACH_MODE PTRACE_ATTACH
# endif // LINUX_VERSION_CODE <= KERNEL_VERSION(3, 4, 0)
#else 
#define PTRACE_ATTACH_MODE PTRACE_ATTACH
#endif 

#ifdef __cplusplus
extern "C" {
#endif

void trace_start();


#ifdef __cplusplus
}
#endif

#endif /* TRACE_H */

