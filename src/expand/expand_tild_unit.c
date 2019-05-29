/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tild_unit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 20:03:41 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 21:49:14 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int			expand_tild_check(int index, char *str)
{
	int				i;

	i = 0;
	while (str[i] && i < index)
		i++;
	if (!str[i] || str[i] != '~')
		return (0);
	return (1);
}

static int			expand_tild_buff(char **str, int *index, char *exp, int del)
{
	char			*fresh;
	size_t			len;
	size_t			len_exp;

	len = ft_strlen(*str);
	len_exp = ft_strlen(exp);
	if (!(fresh = ft_strnew(len + len_exp - del)))
		return (1);
	ft_strncpy(fresh, *str, *index);
	ft_strcpy(&(fresh[*index]), exp);
	ft_strcpy(&(fresh[*index + len_exp]), &(*str)[*index + del]);
	*index += (int)ft_strlen(exp);
	ft_strdel(&(*str));
	*str = fresh;
	return (0);
}

static char			*expand_tild_getroot(char *str)
{
	int				i;

	i = 0;
	while (str[i] && !ft_strchr(" /", str[i]))
	{
		if (!ft_isalnum(str[i]) && !ft_strchr("+-", str[i]))
			return (NULL);
		i++;
	}
	if (!str[i] && !i)
		return (ft_strdup("~"));
	return (ft_strsub(str, 0, i + 1));
}

static int			expand_tild_compare(char *root, char **str, int *index)
{
	static char		*carac[7] = {" ", "~", "/", "+", "+/", "-", "-/"};
	static char		*ext[8] = {"$HOME", "$HOME", "$HOME/", "$PWD", "$PWD/",
		"$OLDPWD", "$OLDPWD/", "/Users/"};
	static int		del[8] = {1, 1, 2, 2, 3, 2, 3, 1};
	int				i;

	i = -1;
	while (++i < 7)
		if (!ft_strcmp(root, carac[i]))
			return (expand_tild_buff(str, index, ext[i], del[i]));
	i = 0;
	while (root[i] && ft_isalnum(root[i]))
		i++;
	if (!root[i] || ft_strchr("/", root[i]))
		return (expand_tild_buff(str, index, ext[7], del[7]));
	return (1);
}

int					expand_tild_unit(char **str, int *index)
{
	char			*root;
	int				ret;

	if (!expand_tild_check(*index, *str))
		return (1);
	if (!(root = expand_tild_getroot(&(*str)[*index + 1])))
		return (1);
	ret = expand_tild_compare(root, str, index);
	ft_strdel(&root);
	return (ret);
}
