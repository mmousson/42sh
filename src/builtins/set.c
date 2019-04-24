/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 21:24:53 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/25 00:31:23 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "set.h"
#include <stdio.h>

static int	list_shell_variables(void)
{
	t_vars	*current;

	current = shell_var_list;
	while (current)
	{
		ft_putstr(current->name);
		ft_putchar('=');
		ft_putendl(current->value);
		current = current->next;
	}
	return (SET_OK);
}

static int	parse_options(int argc, char **argv, int *parsed)
{
	int	j;
	int	options;

	options = 0;
	while (++(*parsed) < argc)
	{
		if (ft_strequ(argv[*parsed], "--"))
			return (options);
		else if (argv[*parsed][0] == '-')
		{
			j = 0;
			while (ALLOWED_OPTIONS[j] != '\0')
				j++;
			if (ALLOWED_OPTIONS[j] == '\0')
				return (-1);
			else
				options |= 1 << j;
		}
		else
			return (options);
	}
	return (options);
}

// static int	set_lineedit_mode(char *mode)
// {
// 	if (mode == NULL)
// 	{
// 		ft_putstr("emacs\t");
// 		ft_putstr(vi_on ? "off" : "on");
// 		ft_putstr("vi\t\t");
// 		ft_putstr(vi_on ? "on" : "off");
// 	}
// 	else
// 	{
// 		if (ft_strequ(mode, "vi"))
// 			vi_on = 1;
// 		else if (ft_strequ(mode, "emacs"))
// 			vi_on = 0;
// 		else
// 		{
// 			ft_putstr_fd("42sh: set: ", STDERR_FILENO);
// 			ft_putstr_fd(mode, STDERR_FILENO);
// 			ft_putendl_fd("invalid option name", STDERR_FILENO);
// 			return (SET_UNAVAILABLE_OPTION);
// 		}
// 	}
// 	return (SET_OK);
// }

int			set(int argc, char **argv, char ***env)
{
	int	options;
	int	parsed;

	(void)env;
	parsed = 0;
	if (argc == 1)
		return (list_shell_variables());
	printf("hello\n");
	if ((options = parse_options(argc, argv, &parsed)) == -1)
		return (SET_UNAVAILABLE_OPTION);
	argc -= parsed;
	argv += parsed;
	printf("argc = %d\n", argc);
	printf("argv[0] = %s\n", argv[0]);
	// if (options & (1 << O_INDEX))
	// 	return (set_lineedit_mode(argc ? argv[0] : NULL));
	return (0);
}
