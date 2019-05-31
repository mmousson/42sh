/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_curly.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 09:18:57 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/31 15:33:08 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "sh42.h"
#include "expand.h"
#include "libft.h"

static char	*take_word_expand(const char *str, char ***arge)
{
	int		k;
	char	*word;
	int		pile;

	pile = 1;
	k = 0;
	while (str[k] && pile)
	{
		if (str[k] == '$' && str[k + 1] == '{')
			pile++;
		else if (str[k] == '}')
			pile--;
		k++;
	}
	word = ft_strsub(str, 0, k - 1);
	expand_param_word(&word, arge);
	return (word);
}

static void	compute_word(char **value, char ***arge, const char *str, int end)
{
	if (str[end] != ':')
		return ;
	if (str[end + 1] == '-')
		if (!(*value))
			*value = take_word_expand(str + end + 2, arge);
	if (str[end + 1] == '+')
		if (*value)
		{
			free(*value);
			*value = take_word_expand(str + end + 2, arge);
		}
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
		else if (pile == 1 && !end_var && !is_char_exp(str[k]))
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
	if (end_var != k && str[end_var] != ':')//to adapt with :- :+ ## %%
	{
		*error = -1;
		return (NULL);
	}
	var = ft_strsub(str, 0, end_var);
	if (!(value = get_spec_param(str)))
		value = utility_get_param(var, *arge);
	compute_word(&value, arge, str, end_var);
	ft_strdel(&var);
	return (value);
}
