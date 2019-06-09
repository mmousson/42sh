/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_builtin_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:51:35 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/09 15:55:23 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "sh42.h"
#include "job_control_42.h"

/*
**
*/

static void	bad_fd(int bad_fd, t_process *proc)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putnbr_fd(bad_fd, STDERR_FILENO);
	ft_putendl_fd(": Bad file descriptor", STDERR_FILENO);
	proc->completed = true;
	proc->valid_to_wait_for = false;
	proc->status = 1;
}

/*
**	Function used to setup builtin I/O channels redirections when they are
**	alone in a pipeline loop
**	If a channel is being redirected, its original File Descriptor is saved
**		 in its counterpart in 'builtin_bkp' struct
**
**	Arguments:
**	proc -> A pointer to the Data-Structure holding informations about the
**		builtin process
**
**	Return Value: NONE
*/

void	job_builtin_redirect(t_process *proc)
{
	t_lstfd	*fds;

	fds = proc->lstfd;
	while (fds != NULL)
	{
		if (fds->og != -1 && (fds->bkp = dup(fds->og)) == -1)
			return (bad_fd(fds->og, proc));
		else if (fds->dir != -1)
		{
			if (dup2(fds->dir, fds->og) == -1)
				return (bad_fd(fds->dir, proc));
			else if (fds->dir_creat)
				close(fds->dir);
		}
		else if (fds->close)
			close(fds->og);
		fds = fds->next;
	}
}

/*
**	Function used to restore builtin I/O channels redirections when they are
**	alone in a pipeline loop
**	It is done by checking if a field in 'builtin_bkp' corresponding to an I/O
**	channel is different than (-1), which is the default value assigned to
**	those field when the process Data-Structure is loaded
**
**	Arguments:
**	proc -> A pointer to the Data-Structure holfding informations about the
**		builtin process
**
**	Return Value: NONE
*/

void	job_builtin_restore(t_process *proc)
{
	t_lstfd	*fds;

	fds = proc->lstfd;
	while (fds != NULL)
	{
		if (!isatty(fds->og))
			dup2(fds->bkp, fds->og);
		close(fds->bkp);
		fds = fds->next;
	}
}
