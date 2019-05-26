#include "line_edition.h"

void			auto_ls(int index, char **name, char **desc, int *loop)
{
	static char	*flag_tab[32] = {
		"-1", "-A", "-B", "-C", "-F", "-H", "-L", "-P", "-R", "-S", "-T", "-a",
		"-b", "-c", "-d", "f", "-g", "-h", "-i", "-k", "-l", "-m", "-n", "-o",
		"-p", "-q", "r", "s", "t", "u", "w", "x"};
	static char	*desc_tab[32] = {
		"  -- single column output", "  -- list all except . and ..",
		"  -- print octal escapes for control characters",
		"  -- list entries in columns sorted vertically", "  -- append file type indicators"
		"  -- follow symlinks on the command line", "  -- list referenced file for sym link",
		"  -- do not follow symlinks", "  -- list subdirectories recursively",
		"  -- sort by size", "  -- show complete time information",
		"  -- list entries starting with .", "  -- as -B, but use C escape codes whenever possible",
  		"  -- status change time", "  -- list directory entries instead of contents",
  		"  -- output is not sorted", "  -- long listing but without owner information",
  		"  -- print sizes in human readable form", "  -- print file inode numbers",
  		"  -- print sizes of 1k", " -- long listing", " -- comma separated", " -- numeric uid, gid",
  		" -- display file flags", " -- append file type indicators for directory",
  		" -- hide control chars", " -- reverse sort order", " -- display size of each file in blocks",
		" -- sort by modification time", " -- access time", " -- print raw characters",
		" -- sort horizontally"};

		*name = ft_strdup(flag_tab[index]);
		*desc = ft_strdup(desc_tab[index]);
		*loop = 32;
}
