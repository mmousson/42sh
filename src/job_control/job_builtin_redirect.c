/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_builtin_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:51:35 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/15 13:13:06 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <fcntl.h>
#include "libft.h"
#include "job_control_42.h"

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

void		job_builtin_redirect(t_process *proc)
{
	t_lstfd	*fds;

	fds = proc->lstfd;
	while (fds != NULL)
	{
		if (fds->og > -1 && (fds->bkp = fcntl(fds->og, F_DUPFD, 10)) == -1)
		{
			job_bad_fd(fds->og, proc);
			return ;
		}
		else if (fds->dir > -1)
		{
			if (dup2(fds->dir, fds->og) == -1)
			{
				job_bad_fd(fds->dir, proc);
				return ;
			}
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
**	It is done by using the 'bkp' field in the 't_lstfd' data-structure
**
**	Arguments:
**	proc -> A pointer to the Data-Structure holding informations about the
**		builtin process
**
**	Return Value: NONE
*/

void		job_builtin_restore(t_process *proc)
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
