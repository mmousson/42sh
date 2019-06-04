/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:26:00 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/04 17:26:00 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

int	blt_fc_list(t_options_infos *inf)
{
	ft_putstr_fd("Starting listing procedure from: ", STDERR_FILENO);
	ft_putstr_fd(inf->first, 2);
	ft_putstr_fd(" to: ", STDERR_FILENO);
	ft_putendl_fd(inf->last, 2);
	return (0);
}