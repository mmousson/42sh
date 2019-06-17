/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_format_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:32:04 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/17 10:00:18 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

static void	write_status(t_job *current, int options)
{
	if (options & 1 << JOBS_L_INDEX)
	{
		if (job_is_stopped(current, DONT_SAVE_CONF))
		{
			ft_putstr("Suspended: ");
			ft_putnbr(current->status);
			ft_putstr("\t\t");
		}
		else if (job_is_completed(current, DONT_FREE_JOB))
		{
			ft_putstr("Done: ");
			ft_putnbr(current->status);
			ft_putstr("\t\t");
		}
		else
			ft_putstr("Running\t\t");
		return ;
	}
	if (job_is_stopped(current, DONT_SAVE_CONF))
		ft_putstr("Stopped\t\t");
	else if (job_is_completed(current, DONT_FREE_JOB))
		ft_putstr("Done\t\t");
	else
		ft_putstr("Running\t\t");
}

void		format_job_info(t_job *head, int options, int i)
{
	if (options == 0 || (options & 1 << JOBS_L_INDEX))
	{
		ft_putchar('[');
		ft_putnbr(i);
		ft_putchar(']');
	}
	if (head->next == NULL && !(options & 1 << JOBS_P_INDEX))
		ft_putchar('+');
	else if (head->next && !head->next->next && !(options & 1 << JOBS_P_INDEX))
		ft_putchar('-');
	else if (!(options & 1 << JOBS_P_INDEX))
		ft_putchar(' ');
	if (!(options & 1 << JOBS_P_INDEX))
		ft_putchar(' ');
	if (!(options & (1 << JOBS_P_INDEX)))
		ft_putstr("\t");
	if (options & (1 << JOBS_P_INDEX) || options & (1 << JOBS_L_INDEX))
		ft_putnbr(head->pgid);
	if (options && (!(options & (1 << JOBS_P_INDEX))))
		ft_putchar('\t');
	if (!(options & (1 << JOBS_P_INDEX)))
		write_status(head, options);
	if (!(options & (1 << JOBS_P_INDEX)))
		ft_putstr(head->command);
	ft_putchar('\n');
}
