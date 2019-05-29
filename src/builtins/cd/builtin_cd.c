/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:09:13 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/29 14:32:38 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "cd.h"
#include "libft.h"

/*
**   http://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
*/

static int	manage_pwd(char ***env, char **cdenv, char *pwd, int options)
{
	if (options & (1 << 28))
		utility_set_var("PWD", getcwd(NULL, 0), env, 0);
	else
		utility_set_var("PWD", pwd, env, 0);
	utility_set_var("OLDPWD", cdenv[2], env, 0);
	return (1);
}

int			change_directory(char ***env, char *pwd, char **cdenv, int options)
{
	if (!check_path_errors(pwd))
		return (0);
	if ((chdir(pwd)) < 0)
	{
		ft_putstr3_fd(""SH_NAME": cd: ", pwd, ": Permission denied\n", 2);
		return (0);
	}
	return (manage_pwd(env, cdenv, pwd, options));
}

static void	init_cdenv(char **cdenv, char **env)
{
	cdenv[0] = utility_get_var("HOME", env);
	cdenv[1] = utility_get_var("OLDPWD", env);
	cdenv[2] = utility_get_var("PWD", env);
	cdenv[3] = utility_get_var("CDPATH", env);
}

int			blt_cd(int argc, char **argv, char ***env)
{
	char			*pwd;
	char			*cdenv[4];
	int				pos_args;
	int				options;

	(void)argc;
	options = 0;
	pos_args = 0;
	pwd = NULL;
	if (!*env)
		return (0);
	if (cd_options_parser(argv, &options, &pos_args) > 0)
		return (1);
	init_cdenv(&cdenv[0], *env);
	if (!(pwd = get_pwd_for_cd(pos_args, argv, &cdenv[0])))
		return (1);
	if (!change_directory(env, pwd, &cdenv[0], options))
	{
		ft_strdel(&pwd);
		return (1);
	}
	ft_strdel(&pwd);
	return (0);
}
