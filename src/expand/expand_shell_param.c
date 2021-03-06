/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_shell_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:51:24 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/09 21:01:12 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int				is_doll_exp(char c)
{
	if (is_char_exp(c))
		return (1);
	if (ft_strchr("{$!?", c))
		return (1);
	return (0);
}

static int		error_substitute(char *str, int j, int end, int error)
{
	char		*sub;

	if (error == -1)
	{
		sub = ft_strsub(str, j, end + 1);
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(sub, 2);
		free(sub);
		ft_putstr_fd(": bad substitution\n", 2);
	}
	return (-1);
}

static int		expand_one_param(char **str, int *j, char ***arge)
{
	char		*expand;
	int			end;
	int			error;

	error = 0;
	end = 0;
	if (!(*str))
		return (0);
	if ((*str)[*j + 1] == '{')
		expand = expand_curly((*str) + *j + 2, arge, &end, &error);
	else
		expand = expand_param((*str) + *j, arge, &end);
	if (error)
		return (error_substitute(*str, *j, end, error));
	if (insert_word(str, expand, *j, end))
		return (1);
	if (expand)
	{
		*j += ft_strlen(expand) - 1;
		ft_strdel(&expand);
	}
	else
		(*j)--;
	return (0);
}

int				expand_param_word(char **str, char ***arge)
{
	char		c;
	int			state;
	int			j;
	int			ret;

	j = 0;
	state = 0;
	while (*str && (c = (*str)[j]))
	{
		if (state % 2 == 1)
			state--;
		else if (c == '\\')
			state++;
		else if (c == '$' && !state && is_doll_exp((*str)[j + 1]))
		{
			if ((ret = expand_one_param(str, &j, arge)))
				return (ret);
		}
		else if (c == '\'')
			state = -state + 2;
		j++;
	}
	return (0);
}

int				expand_shell_param(char **str, char ***arge)
{
	int			ret;

	if (!str || !(*str))
		return (1);
	if ((ret = expand_param_word(str, arge)))
		return (ret);
	return (0);
}
