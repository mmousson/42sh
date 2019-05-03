/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 23:53:08 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/04 00:54:45 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job_control_42.h"

/*
**	Function freeing all allocated data inside a 't_job' Data-Structure
*/

void	job_free(t_job *job)
{
	int			i;
	t_process	*current_process;
	t_process	*next_process;

	ft_strdel(&job->command);
	current_process = job->first_process;
	while(current_process != NULL)
	{
		i = -1;
		next_process = current_process->next;
		while(current_process->argv[++i] != NULL)
			ft_strdel(&current_process->argv[i]);
		ft_strdel(&current_process->argv[i]);
		ft_memdel((void **)&(current_process->argv));
		ft_memdel((void **)&(current_process));
		current_process = next_process;
	}
}
