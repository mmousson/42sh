/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_add_to_active_jobs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:08:19 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/10 18:55:08 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control_42.h"

void	job_add_to_active_job_list(t_job *job)
{
	job->next = g_active_job_list;
	g_active_job_list = job;
}
