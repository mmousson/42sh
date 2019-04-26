/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 09:27:03 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/09 20:32:00 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "job_control_42.h"

/*
**	Lookup table used to convert SIGNAL Numbers into SIGNAL names and
**	messages, or Vice-Versa
**	Global variable defined as 'extern' in includes/job_control_42.h file
*/

t_sig_matcher	g_sig_table[] = {
#ifdef SIGHUP

	{SIGHUP, "SIGHUP", "Terminal hung up"},
#endif
#ifdef SIGINT

	{SIGINT, "SIGINT", "Quit request from job control (^C)"},
#endif
#ifdef SIGQUIT

	{SIGQUIT, "SIGQUIT", "Quit request from job control with core dump (^\\)"},
#endif
#ifdef SIGILL

	{SIGILL, "SIGILL", "Illegal instruction"},
#endif
#ifdef SIGTRAP

	{SIGTRAP, "SIGTRAP", "Trace or breakpoint trap"},
#endif
#ifdef SIGABRT

	{SIGABRT, "SIGABRT", "Abort"},
#endif
#ifdef SIGBUS

	{SIGBUS, "SIGBUS", "Misaligned address error"},
#endif
#ifdef SIGFPE

	{SIGFPE, "SIGFPE", "Floating point exception"},
#endif
#ifdef SIGKILL

	{SIGKILL, "SIGKILL", "Forced quit"},
#endif
#ifdef SIGUSR1

	{SIGUSR1, "SIGUSR1", "User defined signal 1"},
#endif
#ifdef SIGUSR2

	{SIGUSR2, "SIGUSR2", "User defined signal 2"},
#endif
#ifdef SIGSEGV

	{SIGSEGV, "SIGSEGV", "Address boundary error"},
#endif
#ifdef SIGPIPE

	{SIGPIPE, "SIGPIPE", "Broken pipe"},
#endif
#ifdef SIGALRM

	{SIGALRM, "SIGALRM", "Timer expired"},
#endif
#ifdef SIGTERM

	{SIGTERM, "SIGTERM", "Polite quit request"},
#endif
#ifdef SIGCHLD

	{SIGCHLD, "SIGCHLD", "Child process status changed"},
#endif
#ifdef SIGCONT

	{SIGCONT, "SIGCONT", "Continue previously stopped process"},
#endif
#ifdef SIGSTOP

	{SIGSTOP, "SIGSTOP", "Forced stop"},
#endif
#ifdef SIGTSTP

	{SIGTSTP, "SIGTSTP", "Stop request from job control (^Z)"},
#endif
#ifdef SIGTTIN

	{SIGTTIN, "SIGTTIN", "Stop from terminal input"},
#endif
#ifdef SIGTTOU

	{SIGTTOU, "SIGTTOU", "Stop from terminal output"},
#endif
#ifdef SIGURG

	{SIGURG, "SIGURG", "Urgent socket condition"},
#endif
#ifdef SIGXCPU

	{SIGXCPU, "SIGXCPU", "CPU time limit exceeded"},
#endif
#ifdef SIGXFSZ

	{SIGXFSZ, "SIGXFSZ", "File size limit exceeded"},
#endif
#ifdef SIGVTALRM

	{SIGVTALRM, "SIGVTALRM", "Virtual timer expired"},
#endif
#ifdef SIGPROF

	{SIGPROF, "SIGPROF", "Profiling timer expired"},
#endif
#ifdef SIGWINCH

	{SIGWINCH, "SIGWINCH", "Window size change"},
#endif
#ifdef SIGWIND

	{SIGWIND, "SIGWIND", "Window size change"},
#endif
#ifdef SIGIO

	{SIGIO, "SIGIO", "I/O on asynchronous file descriptor is possible"},
#endif
#ifdef SIGPWR

	{SIGPWR, "SIGPWR", "Power failure"},
#endif
#ifdef SIGSYS

	{SIGSYS, "SIGSYS", "Bad system call"},
#endif
#ifdef SIGINFO

	{SIGINFO, "SIGINFO", "Information request"},
#endif
#ifdef SIGSTKFLT

	{SIGSTKFLT, "SIGSTKFLT", "Stack fault"},
#endif
#ifdef SIGEMT

	{SIGEMT, "SIGEMT", "Emulator trap"},
#endif
#ifdef SIGIOT

	{SIGIOT, "SIGIOT", "Abort (Alias for SIGABRT)"},
#endif
#ifdef SIGUNUSED

	{SIGUNUSED, "SIGUNUSED", "Unused signal"},
#endif

	{-1, (void *)0, (void *)0}
};
