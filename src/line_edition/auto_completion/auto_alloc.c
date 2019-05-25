/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:31:57 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/24 10:19:43 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "history.h"

char				*auto_alloc_name(char **str)
{
	int				i;
	char			*fresh;
	char			*tmp;

	i = -1;
	if (!(fresh = ft_strdup(*str)))
		sh_errorterm(TMALLOC);
	while (fresh[++i])
	{
		if (fresh[i] == ' ')
		{
			tmp = fresh;
			if (!(fresh = ft_strnew((int)ft_strlen(fresh) + 1)))
			{
				ft_strdel(&tmp);
				sh_errorterm(TMALLOC);
			}
			ft_strncpy(fresh, tmp, i);
			ft_strcpy(&(fresh[i]), "\\");
			ft_strcpy(&(fresh[i + 1]), &(tmp[i]));
			ft_strdel(&tmp);
			i++;
		}
	}
	return (fresh);
}

char				*auto_delbs(char **str)
{
	int				i;
	char			*fresh;
	char			*tmp;

	i = 0;
	fresh = *str;
	while (fresh[i])
	{
		tmp = fresh;
		if (fresh[i] == '\\' && fresh[i + 1] == ' ')
		{
			if (!(fresh = ft_strnew((int)ft_strlen(fresh) - 1)))
			{
				ft_strdel(&tmp);
				sh_errorterm(TMALLOC);
			}
			ft_strncpy(fresh, tmp, i);
			ft_strcpy(&(fresh[i]), &(tmp[i + 1]));
			ft_strdel(&tmp);
		}
		i++;
	}
	return (fresh);
}

char				*auto_getpath(void)
{
	int				i;
	int				si;
	char			*path;

	i = g_env.cm->pos - 1;
	while (i - g_env.p_size + 1
			&& !auto_newtoken(g_env.line[i], g_env.line[i - 1]))
		i--;
	si = i;
	i = g_env.cm->pos - 1;
	while (i > si && !auto_ispathcarac(g_env.line[i]))
		i--;
	if (si == g_env.cm->pos - 1 || i == si)
		path = ft_strdup("./");
	else if (si + 1 == i)
		path = ft_strsub(g_env.line, si + 1, 1);
	else
		path = ft_strsub(g_env.line, si + 1, i - si);
	if (!path)
		sh_errorterm(TMALLOC);
	return (auto_delbs(&path));
}

char				*auto_getroot(void)
{
	int				i;
	char			*root;

	i = g_env.cm->pos - 1;
	while (i - g_env.p_size + 1
			&& !auto_newtoken(g_env.line[i], g_env.line[i - 1])
			&& !auto_ispathcarac(g_env.line[i])
			&& !auto_isvar(g_env.line[i], g_env.line[i - 1]))
		i--;
	if (!(root = ft_strsub(g_env.line, i + 1, g_env.cm->pos - i - 1)))
		sh_errorterm(TMALLOC);
	return (auto_delbs(&root));
}

void				auto_filldata(void)
{
	char			*path;

	path = NULL;
	g_data.type = auto_getype();
	g_data.root = auto_getroot();
	ft_putnbr(g_data.type);
	if (g_data.type)
		path = auto_getpath();
	else if (g_data.type == 0)
		path = getenv("PATH");
	if (!path || !(g_data.path = ft_strsplit(path, ':')))
		return ;
	if (g_data.type)
		ft_strdel(&path);
	g_data.lw = auto_new_lstword();
	g_data.spos = g_env.cm->pos;
}
