/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control_42.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:33:29 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/09 18:20:38 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_42_H
# define JOB_CONTROL_42_H

# include <sys/types.h>
# include <termios.h>

/*
**	Structure which will be used to to describe an entry for the
**	lookup table used to convert between Sibals IDs and Names
**	and Vice_versa
**	i.e: Matching a SIGNAL number will display a log message
**	along with the SIGNAL name
**	(See job_control/sig_table.c and job_control/mark_process_status.c
**	for in-code usage & definition)
*/

typedef struct			s_sig_matcher
{
	int					signo;
	char				*sig_name;
	char				*msg;
}						t_sig_matcher;

/*
**	Shell PGID and Terminal Configuration that we need to know accross
**	all Job Control's source files
**	Also, the SIGNAL table defintion must be accessible from all Job_Control
**	source files
*/

extern pid_t			shell_proc_group_id;
extern struct termios	shell_term_conf;
extern t_sig_matcher	g_sig_table[];

/*
**	The two first defines will serve to tell the Foreground and Background
**	handlers if a Job is Starting Up or Continuing
**	The two next will simply tell the engine in which group to launch the job
**	The two next will be used to flag the action taken by
**		'first_job_get_or_set' function defined in job_control/sigchl_handler.c
**	The two last will be used to flag waitpid's return value
*/

# define START_JOB 0
# define CONTINUE_JOB 1
# define BACKGROUND_LAUNCH 0
# define FOREGROUND_LAUNCH 1
# define SET 0
# define GET 1
# define WAITPID_ERROR -1
# define WAITPID_NO_MATCH 1

# define STOP_MSG "stopped"
# define COMPLETED_MSG "completed"

/*
**	Boolean data-type
*/

typedef enum			e_bool
{
	false,
	true
}						t_bool;

/*
**	Structure holding I/O channels of a spawned process
*/

typedef struct			s_io_channels
{
	int					input;
	int					output;
	int					error;
}						t_io_channels;

/*
**	Process data-structure
**	pid -> Process ID
**	argv -> Arguments to pass to 'execve' system call
**	environ -> Current environment representation when launching
**	completed -> True if the Process has completed
**	stopped -> True if the Process has stopped
**	foreground -> whether process should be launched in foreground
**	io_channels -> I/O file descriptors
**	next -> Next link of the Process Pipeline
*/

typedef struct			s_process
{
	pid_t				pid;
	char				**argv;
	char				***environ;
	t_bool				completed;
	t_bool				stopped;
	t_io_channels		io_channels;
	t_io_channels		real_channels;
	int					status;
	struct s_process	*next;
}						t_process;

/*
**	A 'job' is a pipeline of processes
**	This is the structure representing it
**	pgid -> Process Group ID
**	command -> Backup of the 'job' command line, used for message display
**	io_channels -> I/O file descriptors
**	notified -> Bool value saving if job's termination/stop has been notified
**	tmodes -> Backup of the terminal modes before launching the 'job'
**	next -> Next Active 'job'
*/

typedef struct			s_job
{
	pid_t				pgid;
	t_process			*first_process;
	char				*command;
	t_io_channels		io_channels;
	t_bool				notified;
	int					status;
	char				***env;
	struct termios		tmodes;
	struct s_job		*next;
}						t_job;

extern t_job			*active_job_list;

/*
**	==================== Job Control's main functions ====================
**
**	job_add_to_active_job_list -> job_control/job_add_to_active_job_list.c
**	job_free -> job_control/job_free.c
**	job_argc -> job_control/job_utility.c
**	job_launch -> job_control/job_engine.c
**	job_command_search_and_exec -> job_control/job_command_search_and_exec.c
**	job_parent_process -> job_control/job_parent_process.c
**	job_child_process -> job_control/job_child_process.c
**	job_send_to_foreground -> job_control/job_foreground.c
**	job_send_to_background -> job_control/job_background.c
**	job_wait_completion -> job_control/job_engine.c
** 	job_mark_process_status -> job_control/job_mark_process_status.c
**	job_update_status -> job_control/job_update_job_status.c
**	job_unstop -> job_control/job_update_job_status.c
**	job_sigchld_handler -> job_control/job_sigchld_handler.c
*/

void					job_add_to_active_job_list(t_job *job);
void					job_free(t_job *job);
int						job_argc(char **argv);
int						job_launch(t_job *job, int fg);
void					job_command_search_and_exec(t_job *job,
	t_process *proc, int fg);
void					job_parent_process(t_job *job, t_process *proc, pid_t pid);
void					job_child_process(t_process *proc, int foreground,
	pid_t pgid);
int						job_send_to_foreground(t_job *job, int must_continue);
int						job_send_to_background(t_job *job, int must_continue);
int						job_wait_completion(t_job *job);
int						job_mark_process_status(t_job *first_job, pid_t pid,
	int status);
void					job_update_status (t_job *first_job);
void					job_unstop(t_job *job, int foreground);
void					job_sigchld_handler(int signo);

/*
**	=================== Job-objects' utility functions ===================
**
**	job_find -> job_control/job_utility.c
**	job_is_stopped -> job_control/job_utility.c
**	job_is_completed -> job_control/job_utility.c
**	job_inform_user_about_completion -> job_control/job_utility.c
**	job_first_job_set_and_get -> job_control/job_sigchld_handler.c
*/

t_job					*job_find (pid_t pgid, t_job *first_job);
int						job_is_stopped(t_job *job);
int						job_is_completed(t_job *job);
void					job_inform_user_about_completion(t_job *j, char *msg);
void					job_first_job_set_and_get(t_job **to_set_or_get,
	int set_or_get);

#endif
