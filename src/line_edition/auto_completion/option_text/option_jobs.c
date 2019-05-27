#include "line_edition.h"

int			auto_jobs(int index, char **name, char **desc)
{
	static char	*flag_tab[2] = {"-l", "-p"};
	static char	*desc_tab[2] = {
		"  -- list process IDs",
		"  -- list process groups"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (2);
}
