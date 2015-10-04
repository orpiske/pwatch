/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pwatch.h
 * Author: otavio
 *
 * Created on October 4, 2015, 2:43 PM
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

#ifdef __cplusplus
extern "C" {
#endif

void trace_start();


#ifdef __cplusplus
}
#endif

#endif /* TRACE_H */

