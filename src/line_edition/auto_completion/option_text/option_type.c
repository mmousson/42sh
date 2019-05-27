#include "line_edition.h"

int			auto_type(int index, char **name, char **desc)
{
	static char	*flag_tab[1] = {
		"-a"};
	static char	*desc_tab[1] = {
		"  -- print all occurrences in path"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (1);
}
