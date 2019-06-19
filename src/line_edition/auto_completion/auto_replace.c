/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:44:15 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/30 14:26:19 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int			auto_replace_option(char *str)
{
	int			diff;

	diff = g_env.cm->pos - g_data.spos;
	if (diff > 0)
	{
		g_env.line = line_delchar(diff);
		line_cursor_motion(MLEFT, diff);
		g_data.spos = g_env.cm->pos;
	}
	line_paste(str + 1, 1);
	return (1);
}

void				auto_replace(char *str, int type)
{
	int			size;
	int			i;

	if (g_data.type == 3 && auto_replace_option(str))
		return ;
	i = g_data.spos - 1;
	while (i - g_env.p_size + 1
			&& auto_ischar(g_env.line[i], g_env.line[i - 1]))
		i--;
	size = g_env.cm->pos - i - 1;
	if (size)
	{
		g_env.line = line_delchar(size);
		line_cursor_motion(MLEFT, size);
	}
	line_paste(str, 1);
	if (type == 9 || type == 14)
		line_paste("/", 1);
	else if (g_data.var && (int)ft_strlen(g_data.var) == 2)
		line_paste("}", 1);
}

char				*auto_expand(char **str)
{
	int				i;
	char			*expand_str;

	i = 0;
	expand_str = ft_strdup(*str);
	if (g_data.type != 1)
		return (expand_str);
	while ((*str)[i] && (*str)[i] != '~')
		i++;
	if ((*str)[i] == '~')
		expand_tild_unit(&expand_str, &i);
	expand_shell_param(&expand_str, g_env.env);
	return (expand_str);
}
