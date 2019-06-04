/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_curly.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 09:18:57 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/04 21:30:43 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "sh42.h"
#include "expand.h"
#include "libft.h"

static void two_point(char **value, char ***arge, const char *str, char *var)
{
	char	*res;

	if (str[1] == '-' && !*value)
		*value = take_word_expand(str + 2, arge);
	if (str[1] == '+' && *value)
	{
			free(*value);
			*value = take_word_expand(str + 2, arge);
	}
	if (str[1] == '=' && !*value)
	{
		res = take_word_expand(str + 2, arge);
		utility_set_var(var, res, arge, 1);
		*value = res;
	}
	else if (str[1] == '?' && !*value)
		expand_question(var, str, arge);
}

static void	compute_word(char **value, char ***arge, const char *str, char *var)
{
	if (str[0] == ':')
		two_point(value, arge, str, var);
	else if (ft_strchr("#%", str[0]))
		expand_glo(value, str, var, arge);
	}

static int	is_valid_line(const char *str)
{
	if (is_doll_exp(str[0]) && !is_char_exp(str[0]) && is_char_exp(str[1]))
		return (0);
	if (is_doll_exp(str[0]))
		return (1);
	return (0);
}

char		*expand_curly(const char *str, char ***arge, int *end, int *error)
{
	int		k;
	int		end_var;
	char	*var;
	char	*value;
	int		pile;

	end_var = 0;
	k = 0;
	pile = 1;
	while (str[k] && pile)
	{
		if (str[k] == '$' && str[k + 1] == '{')
			pile++;
		else if (pile == 1 && !end_var && !is_char_exp(str[k]) && str[k] != '/')
			end_var = k;
		if (str[k] == '}')
			pile--;
		if (pile)
			k++;
	}
	if (!end_var && is_valid_line(str))
		end_var = k;
	*end = k + 1;
	if (str[k])
		(*end)++;
	if (end_var != k && !ft_strchr(":#%", str[end_var]))
	{
		*error = -1;
		return (NULL);
	}
	var = ft_strsub(str, 0, end_var);
	if (!(value = get_spec_param(str)))
		value = utility_get_param(var, *arge);
	compute_word(&value, arge, str + end_var, var);
	ft_strdel(&var);
	return (value);
}
