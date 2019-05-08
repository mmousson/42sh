/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_alloc_wordlst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:07:58 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/07 10:47:06 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void			auto_free_lstword(t_lstword *lstword)
{
	if (!lstword)
		return ;
	if (lstword->next)
		auto_free_lstword(lstword->next);
	if (lstword->name)
		ft_strdel(&(lstword->name));
	ft_memdel((void**)&lstword);
}

t_lstword		*auto_new_lstword(void)
{
	t_lstword	*lstword;

	if (!(lstword = (t_lstword*)ft_memalloc(sizeof(t_lstword))))
		sh_errorterm(TMALLOC);
	return (lstword);
}

static void		auto_add_lstword(t_lstword *lstword, char *name, int type)
{
	t_lstword	*tmp;

	tmp = lstword;
	while (lstword->next)
		lstword = lstword->next;
	if (!(lstword->next = (t_lstword*)ft_memalloc(sizeof(t_lstword))))
	{
		auto_free_lstword(tmp);
		sh_errorterm(TMALLOC);
	}
	if (!(lstword->name = ft_strdup(name)))
	{
		auto_free_lstword(tmp);
		sh_errorterm(TMALLOC);
	}
	lstword->type = type;
	lstword = tmp;
}

void			auto_lstword(t_lstword *lstword, char *name, int type)
{
	if (!lstword)
		return ;
	if (!lstword->name)
	{
		if (!(lstword->name = ft_strdup(name)))
		{
			auto_free_lstword(lstword);
			sh_errorterm(TMALLOC);
		}
		lstword->type = type;
	}
	else
		auto_add_lstword(lstword, name, type);
}
