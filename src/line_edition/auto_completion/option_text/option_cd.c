#include "line_edition.h"

int			auto_cd(int index, char **name, char **desc)
{
	static char	*flag_tab[2] = {"-L", "-P"};
	static char	*desc_tab[2] = {
		"  -- force symbolic links to be followed",
		"  -- use the physical directory structure without following symbolic links"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (2);
}
