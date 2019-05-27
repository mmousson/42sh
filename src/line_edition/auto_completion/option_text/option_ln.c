#include "line_edition.h"

int			auto_ln(int index, char **name, char **desc)
{
	static char	*flag_tab[7] = {"-F", "-f", "-i", "-n", "-h", "-s", "-v"};
	static char	*desc_tab[7] = {
		"  -- remove existing destination directories",
		"  -- remove existing destination files",
		"  -- prompt before removing destination files",
		"  -- do not dereference destination",
		"  -- do not dereference destination",
		"  -- create symbolic links instead of hard links",
		"  -- print name of each linked file"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (7);
}
