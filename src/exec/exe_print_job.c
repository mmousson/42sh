/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_print_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 09:41:35 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/10 13:22:20 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control_42.h"
#include "libft.h"

void		exe_print_chan(t_io_channels chan)
{
	ft_putstr("input  :  ");
	ft_putnbr(chan.input);
	ft_putstr("\noutput :  ");
	ft_putnbr(chan.output);
	ft_putstr("\nerror  :  ");
	ft_putnbr(chan.error);
	ft_putchar('\n');
}

void		exe_print_proc(t_process *proc)
{
	if (proc)
	{
		ft_putstr("   ==== proc ====\n");
		ft_print_words_tables(proc->argv);
		exe_print_proc(proc->next);
	}
}

void		exe_print_job(t_job *job)
{
	ft_putstr("   ==== job ====\n");
	exe_print_proc(job->first_process);
}
