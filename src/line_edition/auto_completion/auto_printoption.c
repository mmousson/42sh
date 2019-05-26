#include "line_edition.h"

static void		auto_getfunc(int index)
{
	char		*name;
	char		*desc;
	int		loop;
	int		i;
	static void	(*lst_command[COMWOPT])(int, char**, char**, int*) = {
		auto_ls};

	i = -1;
	loop = 1;
	name = NULL;
	desc = NULL;
	while (++i < loop)
	{
		lst_command[index](index, &name, &desc, &loop);
		if (!name || !desc)
			sh_errorterm(TMALLOC);
		else
			auto_lstoption(&name, &desc);
	}
}

void			auto_printoption(void)
{
	static char	*command[COMWOPT] = {
		"ls", NULL};
	int		i;

	i = -1;
	if (g_data.type != 3 || !g_data.com_option)
		return ;
	while (command[++i])
	{
		if (!ft_strcmp(command[i], g_data.com_option))
			auto_getfunc(i);
	}
}
