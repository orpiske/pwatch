/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pwatch.c
 * Author: otavio
 *
 * Created on October 4, 2015, 2:43 PM
 */

#include "trace.h"

static void trace_print_siginfo(pid_t pid) {
    siginfo_t siginfo;
    messenger msg = get_messenger();

    ptrace(PTRACE_GETSIGINFO, pid, NULL, &siginfo);

    msg(DEBUG, "Signal code: %d", siginfo.si_code);
    msg(DEBUG, "Tracee received signal %d", siginfo.si_signo);
    msg(DEBUG, "PID: %d", siginfo.si_pid);
    msg(DEBUG, "UID: %d", siginfo.si_uid);
}

static void trace_do_check() {
    const options_t *options = get_options_object();
    messenger msg = get_messenger();
    int status = 0;

    ptrace(PTRACE_CONT, options->pid, NULL, NULL);
    do {
        pid_t ret = waitpid(options->pid, &status, WUNTRACED | WCONTINUED);

        if (ret == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            msg(DEBUG, "exited, status=%d", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            msg(DEBUG, "killed by signal %d", WTERMSIG(status));
            trace_print_siginfo(options->pid);
        } else if (WIFSTOPPED(status)) {
            if (WSTOPSIG(status) == SIGINT) {
                msg(DEBUG, "interrupted %d", WSTOPSIG(status));
                trace_print_siginfo(options->pid);

                kill(options->pid, WSTOPSIG(status));

                break;
            } else {
                if (WSTOPSIG(status) == SIGTERM) {
                    msg(DEBUG, "terminated %d", WSTOPSIG(status));
                    trace_print_siginfo(options->pid);

                    kill(options->pid, WSTOPSIG(status));
                    break;
                }
            }

            msg(DEBUG, "stopped by signal %d", WSTOPSIG(status));
            ptrace(PTRACE_CONT, options->pid, NULL, NULL);
        } else if (WIFCONTINUED(status)) {
            msg(DEBUG, "continued");
        }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
}

void trace_start() {
    const options_t *options = get_options_object();
    messenger msg = get_messenger();

    long ret = 0;
    ret = ptrace(PTRACE_SEIZE, options->pid, NULL, NULL);

    trace_do_check();
    msg(DEBUG, "ptrace exit code: %ld", ret);


    if (strlen(options->command) > 0) {
        msg(DEBUG, "Running command '%s'", options->command);

        // TODO: break the arguments ...
        execlp(options->command, NULL, NULL);
    }
}

