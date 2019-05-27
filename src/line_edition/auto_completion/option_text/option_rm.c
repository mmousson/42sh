#include "line_edition.h"

int			auto_rm(int index, char **name, char **desc)
{
	static char	*flag_tab[4] = {"-R", "-r", "-f", "-i"};
	static char	*desc_tab[4] = {
		"  -- remove directories and their contents recursively",
		"  -- remove directories and their contents recursively",
		"  -- ignore nonexistent files, never prompt",
		"  -- prompt before every removal"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (4);
}
