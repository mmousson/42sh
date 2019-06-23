/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd_for_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 22:33:38 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/23 13:38:23 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "cd.h"
#include "libft.h"

static int		home_cd(char **pwd, char **cdenv, int options)
{
	char			*str;

	if (!cdenv[0])
	{
		ft_putendl_fd(""SH_NAME": cd: HOME not set", 2);
		return (0);
	}
	if (!(str = ft_strdup((cdenv)[0])))
		return (0);
	*pwd = get_final_path(&str, cdenv, options);
	ft_strdel(&str);
	return (1);
}

static int		oldpwd_cd(char **pwd, char **cdenv, int options)
{
	char			*str;

	if (!cdenv[1])
	{
		ft_putendl_fd(""SH_NAME": cd: OLDPWD not set", 2);
		return (0);
	}
	if (!(str = ft_strdup((cdenv)[1])))
		return (0);
	*pwd = get_final_path(&str, cdenv, options);
	ft_putendl_fd(*pwd, 1);
	ft_strdel(&str);
	return (1);
}

char			*get_pwd_for_cd(int pos_args, char **args, char **cdenv,
																int options)
{
	char		*pwd;
	char		*str;

	if (pos_args == 0 || !args[pos_args] || !args[pos_args][0])
	{
		if (!home_cd(&pwd, cdenv, options))
			return (0);
	}
	else if (ft_strcmp(args[pos_args], "-") == 0)
	{
		if (!oldpwd_cd(&pwd, cdenv, options))
			return (0);
	}
	else
	{
		if (!(str = ft_strdup(args[pos_args])))
			return (0);
		pwd = get_final_path(&str, cdenv, options);
		ft_strdel(&str);
	}
	return (pwd);
}
