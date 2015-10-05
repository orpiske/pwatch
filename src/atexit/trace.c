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
#include "trace.h"

static void trace_print_siginfo(pid_t pid)
{
	siginfo_t siginfo;
	messenger msg = get_messenger();

	ptrace(PTRACE_GETSIGINFO, pid, NULL, &siginfo);

	const char *sigcode_text = trace_get_sigcode_text(siginfo.si_code);
	const char *signo_text = trace_get_signo_text(siginfo.si_signo);
	const char *signo_desc = strsignal(siginfo.si_signo);

	msg(INFO, "Signal: %s (%s). Signal code text: %s. PID: %d. UID: %d",
		signo_text, signo_desc, sigcode_text, siginfo.si_pid, siginfo.si_uid);
}

static bool trace_is_running(pid_t pid)
{
	int status = 0;
	messenger msg = get_messenger();

	usleep(500);
	pid_t ret = waitpid(pid, &status, 0);


	// TODO: this is ridiculous -> check for errno and all the stuff
	if (ret == -1) {
		msg(ERROR, "Unable to get process status");

		return false;
	}

	if (WIFEXITED(status)) {
		msg(ERROR, "The process is not running anymore");
		return false;

	}

	msg(INFO, "The process is still running");
	return true;
}

static void trace_tracee_stopped(int status, int pid) {
	messenger msg = get_messenger();
	
	switch (WSTOPSIG(status)) {
	case SIGINT:
		msg(INFO, "Tracee process interrupted");
		break;
	case SIGTERM:
		msg(INFO, "Tracee process terminated");
		break;
	default:
		msg(DEBUG, "Tracee process stopped by signal");
		break;
	}

	trace_print_siginfo(pid);
	/**
	 * We have to make sure that it continues and passes the signal to the 
	 * tracee. That's why we call ptrace with the data argument as 
	 * WSTOPSIG(status) - the signal number - so that when the kernel wakes
	 * up the process, it delivers the signal
	 */
	ptrace(PTRACE_CONT, pid, NULL, WSTOPSIG(status));
}

static void trace_tracee_signaled(int status, int pid) {
	messenger msg = get_messenger();
	
	msg(DEBUG, "Tracee process was killed with signal: %d", 
		WTERMSIG(status));
	
	trace_print_siginfo(pid);
}

static void trace_tracee_exited(int status) {
	messenger msg = get_messenger();
	
	msg(INFO, "Tracee process exited with status: %d", WEXITSTATUS(status));
}

static void trace_do_check()
{
	const options_t *options = get_options_object();
	messenger msg = get_messenger();
	int status = 0;

	ptrace(PTRACE_CONT, options->pid, NULL, NULL);
	do {
		pid_t ret = waitpid(options->pid, &status, 0);

		if (ret == -1) {
			msg(ERROR, "Unable to obtain process details for %d", options->pid);
			return;
		}

		if (WIFEXITED(status)) {
			trace_tracee_exited(status);
		} else if (WIFSIGNALED(status)) {
			trace_tracee_signaled(status, options->pid);
		} else if (WIFSTOPPED(status)) {
			trace_tracee_stopped(status, options->pid);
		} else {
			ptrace(PTRACE_CONT, options->pid, NULL, NULL);
		}
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}

void trace_start()
{
	const options_t *options = get_options_object();
	messenger msg = get_messenger();

	long ret = 0;
	ret = ptrace(PTRACE_SEIZE, options->pid, NULL, NULL);
	msg(TRACE, "Syscall ptrace seize exited with code: %ld", ret);

	trace_do_check();

	ret = ptrace(PTRACE_DETACH, options->pid, NULL, NULL);
	msg(TRACE, "Syscall ptrace detach exited with code: %ld", ret);

	if (strlen(options->command) > 0) {
		msg(DEBUG, "Running command '%s'", options->command);

		// TODO: break the arguments ...
		execlp(options->command, NULL, NULL);
	}
}

