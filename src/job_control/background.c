/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 09:03:36 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/08 12:12:54 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job_control_42.h"

int	send_job_to_background(t_job *job, int must_continue)
{
	(void)job;
	(void)must_continue;
	ft_putendl("Sent to BACKGROUND :(");
	return (1);
}
