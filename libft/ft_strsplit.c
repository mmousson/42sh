/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 05:56:33 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/09 07:42:25 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free_index(char **tab, int index)
{
	int i;

	i = -1;
	while (++i < index)
		free(tab[i]);
	free(tab);
	return (NULL);
}

static int	ft_word_length(char const *s, char c)
{
	int res;

	res = 0;
	while (*s == c && *s != '\0')
		s++;
	while (*s != c && *s != '\0')
	{
		s++;
		res++;
	}
	return (res);
}

static int	ft_count_parts(char const *s, char c)
{
	int i;
	int res;

	i = -1;
	res = 0;
	while (s[++i])
	{
		if (s[i] != c && i == 0)
			res++;
		else if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			res++;
	}
	return (res);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		nb_words;
	char	**res;

	i = -1;
	if (!s)
		return (NULL);
	nb_words = ft_count_parts(s, c);
	if (!(res = (char **)malloc((nb_words + 1) * sizeof(char *))))
		return (NULL);
	res[nb_words] = NULL;
	while (++i < nb_words)
	{
		j = -1;
		if (!(res[i] = (char *)malloc(ft_word_length(s, c) + 1)))
			return (ft_free_index(res, i));
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
			res[i][++j] = *s++;
		res[i][++j] = '\0';
	}
	return (res);
}
