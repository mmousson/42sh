#include "line_edition.h"

static void	ft_endrjump(void)
{
	int	i;

	i = g_env.cm->pos + 1;
	if (i >= g_env.len)
		return ;
	while (g_env.line[i] && (g_env.line[i] == ' ' || g_env.line[i] == '\n'))
		i++;
	while (g_env.line[i] && g_env.line[i] != ' ' && g_env.line[i] != '\n')
		i++;
	if (g_env.line[i - 1])
		ft_cursor_motion(MRIGHT, i - g_env.cm->pos - 1);
}

void		ft_wjump(int count)
{
	while (--count + 1)
		ft_rjump();
}

void		ft_ejump(int count)
{
	while (--count + 1)
		ft_endrjump();
}

void		ft_bjump(int count)
{
	while (--count + 1)
		ft_ljump();
}

void		ft_pipejump(int count)
{
	ft_home(1);
	ft_cursor_motion(MRIGHT, count - 1);
}
