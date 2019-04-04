/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control_42.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 01:46:31 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/04 02:00:39 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_42_H
# define JOB_CONTROL_42_h

# include <termios.h>

/*
**	Boolean data-type
*/

typedef enum			e_bool
{
	false				0;
	true				1;
}						t_bool;

/*
**	Process data-structure
**	pid -> Process ID
**	argv -> Arguments to pass to 'execve' system call
**	completed -> True if the Process has completed
**	stopped -> True if the Process has stopped
**	next -> Next link of the Process Pipeline
*/

typedef struct			s_process
{
	pid_t				pid;
	char				**argv;
	t_bool				completed;
	t_bool				stopped;
	int					status;
	struct s_process	*next;
}						t_process;

/*
**	A 'job' is a pipeline of processes
**	This is the structure representing it
**	pgid -> Process Group ID
**	command -> Backup of the 'job' command line, used for message display
**	stdin, stdout, stderr -> I/O file descriptors
**	tmodes -> Backup of the terminal modes before launching the 'job'
**	next -> Next Active 'job'
*/

typedef struct			s_job
{
	pid_t				pgid;
	t_process			*first_process;
	char				*command;
	int					stdin;
	int					stdout;
	int					stderr;
	struct termios		tmodes;
	struct s_job		*next;
}						t_job;

#endif
