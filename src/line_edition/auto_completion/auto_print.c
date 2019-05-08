/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 09:53:19 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/07 10:48:10 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "line_edition.h"

static int			auto_checkroot(char *name, char *root)
{
	int				len;

	len = (int)ft_strlen(root);
	// return 0 if !root && name start with .
	if (ft_strncmp(name, root, len))
		return (0);
	return (1);
}

int					auto_printword(char *path, char *root)
{
	DIR				*dir;
	struct dirent	*dt;
	t_lstword		*lstword;

	if (!(dir = opendir(path)))
		return (0);
	lstword = auto_new_lstword();
	while ((dt = readdir(dir)))
	{
		if (auto_checkroot(dt->d_name, root))
			auto_lstword(lstword, dt->d_name, dt->d_type);
	}
	while (lstword)
	{
		ft_putendl(lstword->name);
		lstword = lstword->next;
	}
	(void)closedir(dir);
	auto_free_lstword(lstword);
	while (1);
	return (1);
}
