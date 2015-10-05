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
#include <sigutil.h>


const char *trace_get_sigcode_text(int sigcode)
{
	switch (sigcode) {
	case SI_USER:
		return "SI_USER";
	case SI_KERNEL:
		return "SI_KERNEL";
	case SI_QUEUE:
		return "SI_QUEUE";
	case SI_TIMER:
		return "SI_TIMER";
	case SI_MESGQ:
		return "SI_MESGQ";
	case SI_ASYNCIO:
		return "SI_ASYNCIO";
	case SI_SIGIO:
		return "SI_SIGIO";
	case SI_TKILL:
		return "SI_TKILL";
	default:
		return "NONE";
	}
}

const char *trace_get_signo_text(int signo)
{
	switch (signo) {
	case SIGHUP:
		return "SIGHUP";
	case SIGINT:
		return "SIGINT";
	case SIGQUIT:
		return "SIGQUIT";
	case SIGILL:
		return "SIGILL";
	case SIGABRT:
		return "SIGABRT";
	case SIGFPE:
		return "SIGFPE";
	case SIGKILL:
		return "SIGKILL";
	case SIGSEGV:
		return "SIGSEGV";
	case SIGPIPE:
		return "SIGPIPE";
	case SIGALRM:
		return "SIGALRM";
	case SIGTERM:
		return "SIGTERM";
	case SIGUSR1:
		return "SIGUSR1";
	case SIGUSR2:
		return "SIGUSR2";
	case SIGCHLD:
		return "SIGCHLD";
	case SIGCONT:
		return "SIGCONT";
	case SIGSTOP:
		return "SIGSTOP";
	case SIGTSTP:
		return "SIGTSTP";
	case SIGTTIN:
		return "SIGTTIN";
	case SIGTTOU:
		return "SIGTTOU";
	case SIGBUS:
		return "SIGBUS";
	case SIGPOLL:
		return "SIGPOLL";
	case SIGPROF:
		return "SIGPROF";
	case SIGSYS:
		return "SIGSYS";
	case SIGTRAP:
		return "SIGTRAP";
	case SIGURG:
		return "SIGURG";
	case SIGVTALRM:
		return "SIGVTALRM";
	case SIGXCPU:
		return "SIGXCPU";
	case SIGXFSZ:
		return "SIGXFSZ";
	case SIGSTKFLT:
		return "SIGSTKFLT";
	case SIGPWR:
		return "SIGPWR";
	case SIGWINCH:
		return "SIGWINCH";
	default:
		return "UNKNOWN";
	}
}