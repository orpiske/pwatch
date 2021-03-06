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

#ifndef MESSENGER_H_
#define MESSENGER_H_

#include <stdlib.h>

typedef enum message_level_t_ {
	TRACE,
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	FATAL,
} message_level_t;

typedef void(*messenger)(message_level_t level, const char *message, ...);

void set_messenger(messenger new_msg);
messenger get_messenger(void);

//MESSENGER_H
#endif
