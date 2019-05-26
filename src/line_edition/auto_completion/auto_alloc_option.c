#include "line_edition.h"

static void		auto_add_lstoption(char **name, char **desc)
{
	t_lstword	*tmp;

	tmp = g_data.lw;
	while (g_data.lw->next)
		g_data.lw = g_data.lw->next;
	if (!(g_data.lw->next = (t_lstword*)ft_memalloc(sizeof(t_lstword))))
	{
		g_data.lw = tmp;
		sh_errorterm(TMALLOC);
	}
	if (!(g_data.lw->next->name = (t_name*)ft_memalloc(sizeof(t_name))))
		sh_errorterm(TMALLOC);
	g_data.lw->next->name->name = *name;
	g_data.lw->next->name->desc = *desc;
	g_data.lw->next->len = (int)ft_strlen(g_data.lw->name->name);
	g_data.lw->next->type = 7;
	g_data.lw = tmp;
}

void			auto_lstoption(char **name, char **desc)
{
	if (!g_data.lw)
		return ;
	if (!g_data.lw->name)
	{
		if (!(g_data.lw->name = (t_name*)ft_memalloc(sizeof(t_name))))
			sh_errorterm(TMALLOC);
		g_data.lw->name->name = *name;
		g_data.lw->name->desc = *desc;
		g_data.lw->len = (int)ft_strlen(g_data.lw->name->name);
		g_data.lw->type = 7;
	}
	else
		auto_add_lstoption(name, desc);
}
