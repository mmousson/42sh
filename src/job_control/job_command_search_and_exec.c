/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_command_search_and_exec.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:20:38 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/15 16:26:32 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh42.h"
#include "libft.h"
#include "job_control_42.h"

static void	notify_bad_command(t_process *pr, const char *cmd, const char *msg,
	int code)
{
	if (pr->io_channels.input != STDIN_FILENO)
		close(pr->io_channels.input);
	if (pr->io_channels.output != STDOUT_FILENO)
		close(pr->io_channels.output);
	if (pr->next != NULL)
	{
		close(pr->p[0]);
		close(pr->p[1]);
	}
	pr->status = code;
	pr->completed = true;
	pr->valid_to_wait_for = false;
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

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
**	Function launching a process if it is not a built-in utlity
*/

static void	launch_proc(t_job *job, t_process *pr, int fg)
{
	pid_t	pid;

	if ((pid = fork()) == 0)
		job_child_process(job, pr, fg, job->pgid);
	else if (pid > 0)
		job_parent_process(job, pr, pid);
	else
		write(STDERR_FILENO, "Fork Failed\n", 12);
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
**	job ->
**	pr ->
**	fg ->
**	pipe ->
**
**	Return Value: NONE
*/

void		job_command_search_and_exec(t_job *job, t_process *pr, int fg)
{
	int	blt_pos;

	if (job_check_variable_declaration(pr, pr->environ) == DROP_PROCESS)
		return ;
	if (ft_strchr(pr->argv[0], '/') != NULL)
	{
		if (is_path_valid(pr, pr->argv[0]))
			launch_proc(job, pr, fg);
	}
	else
	{
		if (job->first_process->next == NULL
			&& (blt_pos = utility_is_builtin(pr->argv[0])) != -1)
		{
			job->pgid = 0;
			job_open_files(pr);
			job_builtin_redirect(pr);
			pr->status = g_builtins[blt_pos].handler(job_argc(pr->argv),
				pr->argv, pr->environ);
			pr->completed = true;
			pr->valid_to_wait_for = false;
			job_builtin_restore(pr);
		}
		else
			search_using_path(job, pr, fg);
	}
}
