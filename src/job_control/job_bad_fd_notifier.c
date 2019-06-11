/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_bad_fd_notifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:04:53 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/11 13:26:40 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job_control_42.h"

/*
**	Function to notify the user about a Bad File Descriptor used in either
**	a redirection or an agregation
**	Its return value is constant since it is used as the return value of
**	the calling function
**
**	Arguments:
**	bad_fd -> The number of the incorrect 'fd', needed to be displayed
**	proc -> A pointer to the Data structure representing the process
**		(not yet launched) which uses a bad 'fd'
**
**	Return Value: ALWAYS (0)
*/

int	job_bad_fd(int bad_fd, t_process *proc)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putnbr_fd(bad_fd, STDERR_FILENO);
	ft_putendl_fd(": Bad file descriptor", STDERR_FILENO);
	proc->completed = true;
	proc->valid_to_wait_for = false;
	proc->status = 1;
	return (0);
}
