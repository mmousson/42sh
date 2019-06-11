/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 21:24:53 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/11 13:11:14 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"
#include "line_edition.h"

/*
**	Function to print an error message when an invalid option is caught, along
**	with the usage information, all on Standard Error Output (2)
**
**	Arguments:
**	caught_invalid_option -> The actual bad option character
**
**	Return Value: ALWAYS (-1)
*/

static int	usage(char caught_invalid_option)
{
	ft_putstr_fd("42sh: set: -", STDERR_FILENO);
	ft_putchar_fd(caught_invalid_option, STDERR_FILENO);
	ft_putendl_fd(":invalid option", STDERR_FILENO);
	ft_putendl_fd("set: usage: set [-o option-name] [--] [arg ...]",
			STDERR_FILENO);
	return (-1);
}

/*
**	This function displays all the shell's internal variables
**	It is done by looping through the 'shell_var_list' extern variable
**	(declared in includes/sh42.h and initialized in src/core/main.c)
**	The display format is the following: "%s=%s\n", name, value
**
**	Arguments: NONE
**
**	Return Value: ALWAYS SET_OK (0)
*/

static int	list_shell_variables(char **env)
{
	int		i;
	t_vars	*current;

	i = -1;
	while (env[++i] != NULL)
		ft_putendl(env[i]);
	current = g_shell_var_list;
	while (current)
	{
		ft_putstr(current->name);
		ft_putchar('=');
		ft_putendl(current->value);
		current = current->next;
	}
	return (SET_OK);
}

/*
**	This function parses the possible options provided to this utility
**
**	Arguments:
**	argc -> The arguments count
**	argv -> The arguments array
**	parsed -> An int pointer which will be used in the main function to know
**		how many arguments have been read and parsed, so the main function will
**		skip them
**
**	Return Value:
**	(-1)   -> Invalid option provided
**	(>= 0) -> The options have been successfully parsed
*/

static int	parse_options(int argc, char **argv, int *parsed)
{
	int	i;
	int	j;
	int	options;

	options = 0;
	while (++(*parsed) < argc)
	{
		if (ft_strequ(argv[*parsed], "--"))
			return (options);
		else if (argv[*parsed][0] == '-' && !(i = 0))
		{
			while (argv[*parsed][++i] != '\0')
			{
				j = 0;
				while (OPTIONS[j] != '\0' && argv[*parsed][i] != OPTIONS[j])
					j++;
				if (OPTIONS[j] == '\0')
					return (usage(argv[*parsed][i]));
				options |= 1 << j;
			}
		}
		else
			return (options);
	}
	return (options);
}

/*
**	In case the 'o' option has been passed to this utility, this function is
**	called to handle it
**	If 'mode' is NULL, then it means that no 'option_name' has been passed
**	In this case, we just display the status of the available 'option_name'
**
**	Arguments:
**	mode -> The string 'option_name' immediatly following the last 'o' option
**
**	Return Value:
**	SET_UNAVAILABLE_OPTION (2) -> 'mode' does not correspond to a valid option
**		name
**	SET_OK (0) -> Everything went fine
*/

static int	set_lineedit_mode(char *mode)
{
	if (ft_strequ(mode, "vi"))
		vi_new_mode(MVI);
	else if (ft_strequ(mode, "emacs"))
		vi_new_mode(MNORMAL);
	else
	{
		ft_putstr_fd("42sh: set: ", STDERR_FILENO);
		ft_putstr_fd(mode, STDERR_FILENO);
		ft_putendl_fd(": invalid option name", STDERR_FILENO);
		return (SET_UNAVAILABLE_OPTION);
	}
	return (SET_OK);
}

/*
**	============================= BUITLIN COMMAND =============================
**	Main function for the 'set' utility
**	Only accepted option is: -o. Of course, this option will be ignored and
**	treated as a regular argument if the double-hyphen operand "--" is provided
**	beforehand
**	Effect of the 'o' option is to select the active builtin editor during user
**	input which is by default Readline (also called Emacs)
**	Therefore, 'o' option has two possible option_name: 'vi' or 'emacs'
**	The normal behaviour of this utility is to list all the shell's internal
**	variables
**
**	Return Value:
**	SET_OK (0) -> Everything went fine
**	SET_ERROR (1) -> Some error occured (not used in this implementation)
**	SET_INVALID_OPTION (2) -> The user provided an invalid option / option_name
*/

int			blt_set(int argc, char **argv, char ***env)
{
	int	i;
	int	options;
	int	parsed;

	parsed = 0;
	if (argc == 1)
		return (list_shell_variables(*env));
	if ((options = parse_options(argc, argv, &parsed)) == -1)
		return (SET_UNAVAILABLE_OPTION);
	argc -= parsed;
	argv += parsed;
	if (options & (1 << O_INDEX))
		return (set_lineedit_mode(argc ? argv[0] : NULL));
	else
	{
		i = -1;
		while (++i < argc && i <= 9)
			core_spec_var_setget(i + 1, argv[i], SET);
	}
	return (0);
}
