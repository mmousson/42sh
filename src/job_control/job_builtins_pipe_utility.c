/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_builtins_pipe_utility.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:04:16 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/27 00:10:30 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "job_control_42.h"

/*
**	Handle the redirection of I/O channels of Builtin Utilities inside
**	a pipeline loop
**
**	Arguments:
**	proc -> Pointer to a Data-Structure representing the current process
**		being launched
**	pipe (int [2]) -> Int array holding Reading/Writing end of a pipe
**
**	Return Value: The duplicate fd of the original Standard Output
*/

int		job_builtins_pipe_setup(t_process *proc, int *pipe)
{
	int	bkp_fd1;

	if (proc->next == NULL)
		return (-1);
	bkp_fd1 = dup(STDOUT_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[1]);
	return (bkp_fd1);
}

/*
**	Restores a Builtin Utility's redirections resulting from a pipeline loop
**
**	Arguments:
**	proc -> Pointer to a Data-Structure representing the current process
**		being launched
**	bkp_fd1 -> The duplicated fd from the function above of the original
**		Standard Output
**
**	Return Value: NONE
*/

void	job_builtins_pipe_cleanup(t_process *proc, int bkp_fd1)
{
	if (proc->next == NULL)
		return ;
	dup2(bkp_fd1, STDOUT_FILENO);
	close(bkp_fd1);
}
