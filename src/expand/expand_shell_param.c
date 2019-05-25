/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_shell_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:51:24 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/25 14:36:36 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"

static int		is_doll_exp(char c)
{
	if (is_char_exp(c))
		return (1);
	if (c == '{')
		return (1);
	return (0);
}

static int		error_substitute(char *str, int j, int end)
{
	char		*sub;

	sub = ft_strsub(str, j, end + 1);
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(sub, 2);
	free(sub);
	ft_putstr_fd(": bad substitution\n", 2);
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
		return (error_substitute(*str, *j, end));
	if (insert_word(str, expand, *j, end))
		return (1);
	if (expand)
	{
		*j += ft_strlen(expand) - 1;
		ft_strdel(&expand);
	}
	return (0);
}

static int		expand_param_word(char **str, char ***arge)
{
	char		c;
	int			state;
	int			j;
	int			ret;

	j = 0;
	state = 0;
	while ((c = (*str)[j]))
	{
		if (state % 2 == 1)
			state--;
		else if (c == '\\')
			state ++;
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

int		expand_shell_param(char ***argv, char ***arge)
{
	char		**str;
	int			k;
	int			ret;

	if (!argv || !(*argv))
		return (1);
	k = 0;
	while ((str = &((*argv)[k])) && *str)
	{
		if ((ret = expand_param_word(str, arge)))
			return (ret);
		k++;
	}
	return (0);
}
