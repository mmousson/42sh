/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 12:45:57 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/04 17:14:38 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static t_history	*get_link_at(int index)
{
	t_history	*current;

	if (g_env.ry)
		current = g_env.ry->next;
	else
		current = NULL;
	while (current != NULL)
	{
		if ((index += (index > 0) ? -1 : 1) == 0)
			return (current);
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
			return (current);
		current = current->next;
		(*pos)++;
	}
	return (NULL);
}

void				blt_fc_extract(t_options_infos *inf, t_history **from,
	t_history **to)
{
	int	depth;
	int	tmp;
	int	tmp2;

	depth = get_history_depth();
	if (ft_valid_to_atoi(inf->first) && (tmp = ft_atoi(inf->first)))
		*from = get_link_at(ft_clamp(tmp, -depth, depth));
	else
		*from = get_link_from_string(inf->first, &tmp);
	if (inf->last == NULL)
		return ;
	if (ft_valid_to_atoi(inf->last) && (tmp = ft_atoi(inf->last)))
        *to = get_link_at(ft_clamp(tmp, -depth, depth));
    else
    {
        *to = get_link_from_string(inf->last, &tmp2);
        if (tmp > tmp2)
            inf->reversed = !inf->reversed;
    }
}