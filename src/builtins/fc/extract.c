/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 12:45:57 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/04 17:35:55 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fc.h"

static int			get_history_depth(void)
{
	int			result;
	t_history	*current;

	result = 0;
	current = g_env.ry;
	while (current != NULL)
	{
		result++;
		current = current->next;
	}
	return (result);
}

static t_history	*get_link_at(int index, int *pos)
{
	t_history	*current;

	if (g_env.ry)
		current = g_env.ry->next;
	else
		current = NULL;
	while (current != NULL)
	{
		if ((index >= 0 && current->id == index)
			|| (index < 0 && ++index == 0))
		{
			*pos = current->id;
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

static t_history	*get_link_from_string(const char *str, int *pos)
{
	t_history	*current;

	*pos = 0;
	if (g_env.ry)
		current = g_env.ry->next;
	else
		current = NULL;
	while (current != NULL)
	{
		if (ft_strnequ(current->line, str, ft_strlen(str)))
		{
			*pos = current->id;
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

void				blt_fc_extract(t_options_infos *inf)
{
	int			depth;
	int			tmp;
	int			tmp2;
	t_history	*tmp_hist;

	depth = get_history_depth();
	if (ft_valid_to_atoi(inf->first) && (tmp = ft_atoi(inf->first)))
		inf->from = get_link_at(ft_clamp(tmp, -depth, depth), &tmp);
	else
		inf->from = get_link_from_string(inf->first, &tmp);
	if (inf->last == NULL)
		return ;
	if (ft_valid_to_atoi(inf->last) && (tmp2 = ft_atoi(inf->last)))
		inf->to = get_link_at(ft_clamp(tmp2, -depth, depth), &tmp2);
	else
		inf->to = get_link_from_string(inf->last, &tmp2);
	if (inf->reversed)
	{
		tmp_hist = inf->from;
		inf->from = inf->to;
		inf->to = tmp_hist;
	}
	if (ft_abs(tmp) > ft_abs(tmp2))
		inf->reversed = !inf->reversed;
}
