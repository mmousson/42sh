#include "line_edition.h"

int			auto_hash(int index, char **name, char **desc)
{
	static char	*flag_tab[1] = {"-r"};
	static char	*desc_tab[1] = {
		"  -- forget all previously remembered utility locations"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (1);
}
