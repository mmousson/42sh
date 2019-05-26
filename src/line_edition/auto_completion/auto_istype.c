#include "line_edition.h"

int				auto_ispathcarac(char c)
{
	if (c == '/' || c == '<' || c == '>')
		return (1);
	return (0);
}

int				auto_newtoken(char c, char prev)
{
	if ((c == ' ' && prev != '\\') || c == '|' || c == '&' || c == '(')
		return (1);
	return (0);
}

int				auto_isvar(char c, char prev)
{
	if (c == '$' || (c == '{' && prev == '$'))
		return (1);
	return (0);
}

int				auto_isoption(char c, char prev)
{
	if (c == '-' && prev == ' ')
		return (1);
	return (0);
}

void				auto_keep_comp(char *str, int ret)
{
	if (g_data.status == 2 && str[0] != '\t' && str[0] != '\n'
		&& !auto_istabshift(str, ret))
	{
		auto_free();
		ft_bzero(&g_data, sizeof(t_autodata));
	}
}

int				auto_ischar(char c, char prev)
{
	if (!auto_newtoken(c, prev)
		&& !auto_ispathcarac(c)
		&& !auto_isvar(c, prev)
		&& !auto_isoption(c, prev))
			return (1);
	return (0);
}
