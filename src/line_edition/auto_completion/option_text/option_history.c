#include "line_edition.h"

int			auto_history(int index, char **name, char **desc)
{
	static char	*flag_tab[1] = {"--"};
	static char	*desc_tab[1] = {"  -- to do(Robin)"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (1);
}
