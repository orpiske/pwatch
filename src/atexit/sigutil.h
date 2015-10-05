/* 
 * File:   sigutil.h
 * Author: opiske
 *
 * Created on October 5, 2015, 3:26 PM
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

