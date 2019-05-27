#include "line_edition.h"

int			auto_mkdir(int index, char **name, char **desc)
{
	static char	*flag_tab[2] = {"-m", "-p"};
	static char	*desc_tab[2] = {
		"  -- set permission mode",
		"  -- make parent directories as needed"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (2);
}
