/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_command_search_and_exec.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:20:38 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/31 15:40:23 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh42.h"
#include "libft.h"
#include "job_control_42.h"

static void	notify_bad_command(t_process *pr, const char *cmd, const char *msg)
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
	pr->status = 127;
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
			notify_bad_command(pr, path, ": Is a directory");
			return (0);
		}
		else if (access(path, X_OK) == 0)
			return (1);
		else
		{
			notify_bad_command(pr, path, ": Permission denied");
			return (0);
		}
	}
	else
	{
		notify_bad_command(pr, path, ": No such file or directory");
		return (0);
	}
}

/*
**	Function launching a process if it is not a built-in utlity
*/

static void	launch_proc(t_job *job, t_process *proc, int fg)
{
	pid_t	pid;

	if ((pid = fork()) == 0)
		job_child_process(proc, fg, job->pgid);
	else if (pid > 0)
		job_parent_process(job, proc, pid);
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
**	proc -> A pointer to the Data-Structure holding the informations about
**		the process that is being launched
**	fg -> Whther the process/builtin should be launched in foreground
**
**	Return Value: NONE
*/

static void	search_using_path(t_job *job, t_process *proc, int fg)
{
	int		hash;
	char	*to_del;

	if (utility_is_builtin(proc->name) == -1)
	{
		to_del = proc->name;
		hash = hash_string(proc->name);
		if (hash_already_exists(hash, proc->name))
		{
			g_hash[hash].hits += 1;
			proc->name = ft_strdup(g_hash[hash].full_path);
		}
		else if ((proc->name = utility_search(proc->name)) == NULL)
		{
			proc->name = to_del;
			notify_bad_command(proc, to_del, ": Command not found");
			return ;
		}
		ft_strdel(&to_del);
	}
	launch_proc(job, proc, fg);
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
**	proc ->
**	fg ->
**	pipe ->
**
**	Return Value: NONE
*/

void		job_command_search_and_exec(t_job *job, t_process *proc, int fg)
{
	int	blt_pos;

	if (job_check_variable_declaration(proc) == DROP_PROCESS)
		return ;
	if (ft_strchr(proc->argv[0], '/') != NULL)
	{
		if (is_path_valid(proc, proc->argv[0]))
			launch_proc(job, proc, fg);
	}
	else
	{
		if (job->first_process->next == NULL
			&& (blt_pos = utility_is_builtin(proc->argv[0])) != -1)
			{
				job_builtin_redirect(proc);
				proc->status = g_builtins[blt_pos].handler(
					job_argc(proc->argv),
					proc->argv,
					proc->environ);
				proc->completed = true;
				proc->valid_to_wait_for = false;
				job_builtin_restore(proc);
			}
		else
			search_using_path(job, proc, fg);
	}
}
