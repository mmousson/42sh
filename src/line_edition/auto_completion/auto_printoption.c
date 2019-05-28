/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_printoption.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:43:54 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 18:55:52 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int		auto_getfunc(int index, int i, char **name, char **desc)
{
	static int	(*lst_command[COMWOPT])(int, char**, char**) = {
		auto_ls, auto_cat, auto_date, auto_chmod, auto_cp,
		auto_df, auto_echo, auto_kill, auto_ln, auto_mkdir,
		auto_pax, auto_ps, auto_rm, auto_stty, auto_cd,
		auto_type, auto_export, auto_set, auto_unset,
		auto_jobs, auto_unalias, auto_test, auto_hash, auto_fc};

	return (lst_command[index](i, name, desc));
}

static void		auto_fill_option(int index)
{
	char		*name;
	char		*desc;
	int			loop;
	int			i;

	i = -1;
	loop = 1;
	name = NULL;
	desc = NULL;
	while (++i < loop)
	{
		loop = auto_getfunc(index, i, &name, &desc);
		if (!name || !desc)
			sh_errorterm(TMALLOC);
		else if (ft_strchr(g_data.root, *(name + 1)))
		{
			ft_strdel(&name);
			ft_strdel(&desc);
		}
		else
			auto_lstoption(&name, &desc);
	}
}

void			auto_printoption(void)
{
	int			i;
	static char	*command[COMWOPT] = {
		"ls", "cat", "date", "chmod", "cp", "df", "echo",
		"kill", "ln", "mkdir", "pax", "ps", "rm", "stty",
		"cd", "type", "export", "set", "unset",
		"jobs", "unalias", "test", "hash", "fc", NULL};

	i = -1;
	if (g_data.type != 3 || !g_data.com_option)
		return ;
	while (command[++i])
	{
		if (!ft_strcmp(command[i], g_data.com_option))
			auto_fill_option(i);
	}
}
