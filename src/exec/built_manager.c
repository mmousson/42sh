/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:58:07 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/06 22:07:51 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int				ft_do_home(int k, char **argv, char ***arge)
{
	/*
	static int	(*fct_list_home[NB_FCT - 1])(char**, char***) = {
		ft_echo, ft_cd, ft_env, ft_setenv, ft_unsetenv, blt_edition,
		blt_history};

	if (k < NB_FCT && k > 0)
		return (*(fct_list_home[k - 1]))(argv, arge);
	else
		return (0);
		*/
	(void)k;
	(void)argv;
	(void)arge;
	return (0);
}

int				ft_get_home_cmd(char *name)
{
	/*
	int			k;
	static char	*tabl[NB_FCT] = {
		"exit", "echo", "cd", "env", "setenv", "unsetenv", "edition",
		"history"};

	if (!name)
		return (-1);
	k = 0;
	while (k < NB_FCT)
	{
		if (!ft_strcmp(name, tabl[k]))
			return (k);
		k++;
	}*/
	(void)name;
	return (-1);
}
/*
int				ft_error_message(t_berror error)
{
	ft_putstr_fd("error ID=", STDERR_FILENO);
	ft_putnbr_fd(error, STDERR_FILENO);
	ft_putchar('\n');
	return (0);
}*/
