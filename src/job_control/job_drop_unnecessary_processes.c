/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_drop_unnecessary_processes.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:29:41 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/28 18:12:02 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "sh42.h"
#include "job_control_42.h"

/*
**
*/

static void	drop_all_preceeding_processes(t_job *job, t_process *drop_target)
{
	t_process	*next;
	t_process	*to_drop;

	to_drop = job->first_process;
	while (to_drop != drop_target)
	{
		next = to_drop->next;
		if (to_drop->real_channels.input != STDIN_FILENO)
			close(to_drop->real_channels.input);
		if (to_drop->real_channels.output != STDOUT_FILENO)
			close(to_drop->real_channels.output);
		if (to_drop->real_channels.error != STDERR_FILENO)
			close(to_drop->real_channels.error);
		ft_del_words_tables(&to_drop->argv);
		ft_memdel((void **)&(to_drop));
		to_drop = next;
	}
	job->first_process = drop_target;
}

/*
**
*/

void		job_drop_unnecessary_processes(t_job *job)
{
	t_process	*drop_target;
	t_process	*current;

	drop_target = NULL;
	current = job->first_process->next;
	while (current != NULL)
	{
		if (current->real_channels.input != STDIN_FILENO)
			drop_target = current;
		current = current->next;
	}
	if (drop_target != NULL)
		drop_all_preceeding_processes(job, drop_target);
}
