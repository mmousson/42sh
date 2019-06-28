/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_command_search_and_exec.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:20:38 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/28 14:26:12 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "lex.h"
#include "sh42.h"
#include "libft.h"
#include "job_control_42.h"

/*
**	This function is called whenever an invalid pathname is provided as a
**	process command
**
**	Arguments:
**	pr -> A pointer to the Data Strucutre representing the process to be
**		launched
**	cmd -> The name of the file that has been detected as invalid
**	msg -> The error message to display
**
**	Return Value: NONE
*/

static void	notify_bad_command(t_process *pr, const char *cmd, const char *msg,
	int code)
{
	if (pr->io_channels.input != STDIN_FILENO)
		close(pr->io_channels.input);
	if (pr->io_channels.output != STDOUT_FILENO)
		close(pr->io_channels.output);
	pr->status = code;
	pr->completed = true;
	pr->valid_to_wait_for = false;
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

/*
**	This function checks the validity of a directory entry pointed by 'path'
**	A 'path' is considered valid if it points to an existing regular file with
**	execution right for the current user
**	If 'path' is invalid, the function shall call 'notify_bad_command' with
**	an appropriate error message and set the process's status accordingly
**
**	Arguments:
**	pr -> A pointer to the Data Strucutre representing the process to be
**		launched
**	path -> A string holding the path to the file being checked
**
**	Return Value:
**	0 -> The 'path' argument doesn't point to a valid file
**	1 -> The 'path' argument does point to a valid file
*/

static int	is_path_valid(t_process *pr, const char *path)
{
	int	file_type;

	if ((file_type = utility_file_exists(path)) != 0)
	{
		if (file_type == FILETYPE_DIRECTORY)
		{
			notify_bad_command(pr, path, ": Is a directory", 127);
			return (0);
		}
		else if (access(path, X_OK) == 0)
			return (1);
		else
		{
			notify_bad_command(pr, path, ": Permission denied", 126);
			return (0);
		}
	}
	else
	{
		notify_bad_command(pr, path, ": No such file or directory", 127);
		return (0);
	}
}

/*
**	Function launching a process if it is not a built-in utility
**
**	Arguments:
**	job -> A pointer to the Data Structure representing the job being launched
**	pr -> A pointer to the Data Strucutre representing the process to be
**		launched
**	fg -> A boolean value telling whether we should launch the process
**		in foreground or background
**
**	Return Value: NONE
*/

static void	launch_proc(t_job *job, t_process *pr, int fg)
{
	pid_t	pid;

	ft_putendl_fd("Forking", 2);
	if ((pid = fork()) == 0)
		job_child_process(job, pr, fg, job->pgid);
	else if (pid > 0)
		job_parent_process(job, pr, pid);
	else
		write(STDERR_FILENO, "42sh: launch_proc: Fork Failed\n", 31);
}

/*
**	Function searching through the known PATH environment variable
**	for an utility named after the 'prov->argv[0]' string
**	If first checks if the name is available in the hash table, and if not
**	it will call the 'utility_search' function to try and get the full path
**	of the utility
**	If even that function can't find the utility, the shell shall write
**	an error message and set the process' exit status as 127
**
**	Arguments:
**	job -> A pointer to the Data-Structure holding the informations about
**		the job that is being launched
**	pr -> A pointer to the Data-Structure holding the informations about
**		the process that is being launched
**	fg -> Whther the process/builtin should be launched in foreground
**
**	Return Value: NONE
*/

static void	search_using_path(t_job *job, t_process *pr, int fg)
{
	int		hash;
	char	*to_del;

	if (utility_is_builtin(pr->name) == -1)
	{
		to_del = pr->name;
		hash = hash_string(pr->name);
		if (hash_already_exists(hash, pr->name))
		{
			g_hash[hash].hits += 1;
			pr->name = ft_strdup(g_hash[hash].full_path);
		}
		else if (!(pr->name = utility_search(*(pr->environ), pr->name, 1)))
		{
			pr->name = to_del;
			notify_bad_command(pr, to_del, ": command not found", 127);
			return ;
		}
		ft_strdel(&to_del);
	}
	launch_proc(job, pr, fg);
}

/*
** =================> COMMAND SEARCH AND EXECUTION ALGORITHM <================
**	If the command name contains at least one slash, then launch the process
**	with the same name with execve after forking
**
**	If it does not contain any slashes, then:
**		If the command name is a Builtin Utility, then invoke that Utility
**
**		Otherwise, the command shall be searched for using the PATH env var
**			If the search is successful, then launch the name resulting from
**				the search with execve after forking
**
**			If the search is unsuccessful, the command shall fail with
**			an exit status of 127 and the shell shall write an error message
**
**	Arguments:
**	job -> A pointer to the Data Structure representing the job being launched
**	pr -> A pointer to the Data Strucutre representing the process to be
**		launched
**	fg -> A boolean value telling whether we should launch the process
**		in foreground or background
**
**	Return Value: NONE
*/

void		job_command_search_and_exec(t_job *job, t_process *pr, int fg)
{
	int	blt_pos;

	blt_pos = 0;
	dprintf(2, "Starting command search and exec with: %s and %s\n", pr->compound_command, pr->argv[0]);
	if (job_check_variable_declaration(pr, pr->environ) == DROP_PROCESS)
		return ;
	if (pr->compound && pr->subshell)
		launch_proc(job, pr, fg);
	else if (ft_strchr(pr->argv[0], '/') != NULL)
	{
		if (is_path_valid(pr, pr->argv[0]))
			launch_proc(job, pr, fg);
	}
	else if (pr->compound || (job->first_process->next == NULL
		&& (blt_pos = utility_is_builtin(pr->argv[0])) != -1))
		job_launch_inside_process(blt_pos, job, pr);
	else
		search_using_path(job, pr, fg);
}
