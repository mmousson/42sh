#include "line_edition.h"

int			auto_unset(int index, char **name, char **desc)
{
	static char	*flag_tab[2] = {"-f", "-v"};
	static char	*desc_tab[2] = {
		"  -- to do ?",
		"  -- to do ?"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (2);
}
