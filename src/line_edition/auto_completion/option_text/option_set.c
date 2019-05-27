#include "line_edition.h"

int			auto_set(int index, char **name, char **desc)
{
	static char	*flag_tab[1] = {"-o"};
	static char	*desc_tab[1] = {
		"  -- set specified option"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (1);
}
