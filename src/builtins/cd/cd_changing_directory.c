/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_changing_directory.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 01:47:49 by tduval            #+#    #+#             */
/*   Updated: 2019/05/06 01:50:16 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "libft.h"
#include "cd.h"

int	cd_changing_directory(char *dir[2], char ***env, char opts, int f)
{
	char	buf[4096];
	char	*pwd;
	int		i;

	pwd = cd_get_pwd(dir[1]);
	ft_strdel(&(dir[1]));
	if (opts == OPT_P && (i = (int)readlink(pwd, buf, 4096)) != -1)
	{
		f = 0;
		ft_strdel(&pwd);
		pwd = ft_strdup(buf);
		pwd[i - 1] = '\0';
	}
	if (chdir(pwd) != -1)
	{
		ft_putstr("[NOT WRITTEN] CHDDIRED ON ");	// will be removed
		ft_putendl(pwd);							// will be removed
		utility_add_entry_to_environ(env, "OLDPWD",
				utility_get_env_var(env, "PWD"));
		utility_add_entry_to_environ(env, "PWD", pwd);
		ft_strdel(&pwd);
		return (0);
	}
	ft_putstr_fd("cd: could not change directory to: ", 2);
	ft_putendl_fd(f ? dir[0] : pwd, 2);
	ft_strdel(&pwd);
	return (1);
}
