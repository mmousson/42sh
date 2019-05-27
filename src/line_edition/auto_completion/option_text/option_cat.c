#include "line_edition.h"

int			auto_cat(int index, char **name, char **desc)
{
	static char	*flag_tab[7] = {
		"-b", "-e", "-n", "-s", "-t", "u", "v"};
	static char	*desc_tab[7] = {
		"  -- number non-blank output lines",
		"  -- display $ at the end of each line (implies -v)",
		"  -- number all output lines",
		"  -- squeeze multiple blank lines into one",
		"  -- display tab as ^I (implies -v)",
		"  -- do not_buffer output",
		"  -- display non-printing chars as ^X or M-a"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (7);
}
