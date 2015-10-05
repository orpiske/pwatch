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

#ifndef SIGUTIL_H
#define	SIGUTIL_H

#include <signal.h>
#include <string.h>

#ifdef	__cplusplus
extern "C" {
#endif

const char *trace_get_sigcode_text(int sigcode);
const char *trace_get_signo_text(int signo);


#ifdef	__cplusplus
}
#endif

#endif	/* SIGUTIL_H */

