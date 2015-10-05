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
    
    
    msg(DEBUG, "PID: %d", siginfo.si_pid);
    msg(DEBUG, "UID: %d", siginfo.si_uid);
}

static bool trace_is_running(pid_t pid) {
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

static void trace_do_check() {
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
            msg(DEBUG, "exited, status=%d", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            msg(DEBUG, "killed by signal %d", WTERMSIG(status));
            trace_print_siginfo(options->pid);
        } 
        else {
            if (WIFSTOPPED(status)) {
                switch (WSTOPSIG(status)) {
                    case SIGINT: {
                        msg(INFO, "Tracee process interrupted %d", WSTOPSIG(status));
                        break;
                    }
                    case SIGTERM: {
                        msg(DEBUG, "Tracee process terminated %d", WSTOPSIG(status));
                        break;
                    }
                    
                    default: {
                        msg(DEBUG, "Tracee process stopped by signal %d", WSTOPSIG(status));
                        break;
                    }
                }
                
                trace_print_siginfo(options->pid);
                ptrace(PTRACE_CONT, options->pid, NULL, WSTOPSIG(status));
            }
            else {
                ptrace(PTRACE_CONT, options->pid, NULL, NULL);
            }
            
            
        }
        
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
}

void trace_start() {
    const options_t *options = get_options_object();
    messenger msg = get_messenger();

    long ret = 0;
    ret = ptrace(PTRACE_SEIZE, options->pid, NULL, NULL);
    msg(DEBUG, "ptrace seize exit code: %ld", ret);

    trace_do_check();
    
    ret = ptrace(PTRACE_DETACH, options->pid, NULL, NULL);
    msg(DEBUG, "ptrace detach exit code: %ld", ret);
    
    if (strlen(options->command) > 0) {
        msg(DEBUG, "Running command '%s'", options->command);

        // TODO: break the arguments ...
        execlp(options->command, NULL, NULL);
    }
}

