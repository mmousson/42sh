#include "line_edition.h"

int			auto_echo(int index, char **name, char **desc)
{
	static char	*flag_tab[1] = {"-n"};
	static char	*desc_tab[1] = {
		"  -- do not print the trailing newline character"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (1);
}
