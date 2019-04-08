/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control_42.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:33:29 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/08 12:11:16 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_42_H
# define JOB_CONTROL_42_H

# include <sys/types.h>
# include <termios.h>

/*
**	Shell PGID and Terminal Configuration that we need to know accross
**	all Job Control's source files
*/

extern pid_t			shell_proc_group_id;
extern struct termios	shell_term_conf;

/*
**	Those two defines will serve to tell the Foreground and Background
**	handlers if a Job is Starting Up or Continuing
*/

# define START_JOB 0
# define CONTINUE_JOB 1

/*
**	Boolean data-type
*/

typedef enum			e_bool
{
	false,
	true
}						t_bool;

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
	char				**environ;
	t_bool				completed;
	t_bool				stopped;
	t_io_channels		io_channels;
	int					status;
	struct s_process	*next;
}						t_process;

/*
**	A 'job' is a pipeline of processes
**	This is the structure representing it
**	pgid -> Process Group ID
**	command -> Backup of the 'job' command line, used for message display
**	io_channels -> I/O file descriptors
**	tmodes -> Backup of the terminal modes before launching the 'job'
**	next -> Next Active 'job'
*/

typedef struct			s_job
{
	pid_t				pgid;
	t_process			*first_process;
	char				*command;
	t_io_channels		io_channels;
	struct termios		tmodes;
	struct s_job		*next;
}						t_job;

/*
**	==================== Job Control's main functions ====================
**
**	job_launch -> job_control/job_engine.c
**	parent_process -> job_control/parent_process.c
**	child_process -> job_control/child_process.c
**	send_job_to_foreground -> job_control/foreground.c
**	send_job_to_background -> job_control/background.c
*/

int						job_launch(t_job *job, int fg);
void					parent_process(t_job *job, t_process *proc, pid_t pid);
void					child_process(t_process *proc, int foreground,
	pid_t pgid);
int						send_job_to_foreground(t_job *job, int must_continue);
int						send_job_to_background(t_job *job, int must_continue);
int						wait_job_completion(t_job *job);

/*
**	=================== Job-objects' utility functions ===================
**
**	find_job -> job_control/utility.c
**	job_is_stopped -> job_control/utility.c
**	job_is_completed -> job_control/utility.c
*/

t_job					*find_job (pid_t pgid, t_job *first_job);
int						job_is_stopped(t_job *job);
int						job_is_completed(t_job *job);

#endif
