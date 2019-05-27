#include "line_edition.h"

int			auto_unalias(int index, char **name, char **desc)
{
	static char	*flag_tab[1] = {"-a"};
	static char	*desc_tab[1] = {
		"  -- remove all alias definitions"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (1);
}
