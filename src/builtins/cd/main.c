#include "cd.h"
#include "sh42.h"
#include "libft.h"

int		main(int ac, char **av, char **env)
{
	char	**cpy;
	int		i;

	i = 0;
	cpy = utility_duplicate_environ(env);
	blt_cd(ac, av, &cpy);
	ft_putendl("\n --------------------------------- \n");
	while (cpy[i])
	{
		if (ft_strncmp(cpy[i], "PWD", 3) == 0
				|| ft_strncmp(cpy[i], "OLDPWD", 6) == 0)
			ft_putendl(cpy[i]);
		ft_strdel(&(cpy[i]));
		i++;
	}
	ft_memdel((void **)&cpy);
	return (0);
}
