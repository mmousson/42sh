/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 08:24:21 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/24 21:09:54 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unalias.h"

/*
**	Simply deletes an existing alias definition identified by 'token'
**	from the current alias list
**	We loop through the list, and if the 'token' argument is equals to
**	the 'token' key of the list's link we are currently on, we delete
**	all the keys, and the link itself, then update the list hierarchy
**	After all is done, we return (0) the the built-in caller
**
**	In case no match has been found, we return (1) and the main builtin
**	function will display an appropriate error message
**
**	Arguments:
**	token -> The string identifier which will be used to find which alias
**		definition needs to be deleted
**
**	Return Value:
**	0  -> An alias definition matching the 'token' argument has been found
**		and correctly deleted
**	-1 -> No alias defintion matching the 'token' argument has been found,
**		display an error message to the user
*/

static int	delete_element(char *token)
{
	t_alias	*prev;
	t_alias	*current;

	prev = NULL;
	current = g_alias_list;
	while (current)
	{
		if (ft_strequ(current->token, token))
		{
			if (prev)
				prev->next = current->next;
			else if (!prev)
				g_alias_list = current->next;
			ft_strdel(&(current->token));
			ft_strdel(&(current->replacement));
			ft_memdel((void **)&(current));
			utility_write_alias_list_to_file();
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (-1);
}

/*
**	This function will free all alias list's links and empty the file located
**	in the user's HOME directory
**
**	Arguments: NONE
**
**	Return Value: Always (1)
*/

static int	remove_all_aliases(void)
{
	utility_free_alias_list();
	utility_write_alias_list_to_file();
	return (1);
}

/*
**	============================= BUITLIN COMMAND =============================
**	Main function for the 'unalias' utility function
**	Accepted option is "-a". Of course, this option will be ignored and treated
**	as a regular argument if the double-hyphen operand "--" is provided
**	beforehand
**	Effect of "-a" option is to flush the entire alias list
**	The normal behaviour of this utility is to delete every alias definition
**	defined in each of the arguments
**
**	Return Value:
**	0 -> Everything went well
**	1 -> An error occured
*/

int			blt_unalias(int argc, char **argv, char ***env)
{
	int		options_on;
	int		ret;

	(void)env;
	ret = 0;
	options_on = 1;
	while (--argc > 0)
	{
		++argv;
		if (options_on && ft_strequ("-a", argv[0]))
			return (remove_all_aliases());
		else if (options_on && ft_strequ("--", argv[0]))
		{
			options_on = 0;
			continue;
		}
		else if (delete_element(argv[0]) == -1)
		{
			ft_putstr_fd("42sh: unalias: ", STDERR_FILENO);
			ft_putstr_fd(argv[0], STDERR_FILENO);
			ft_putendl_fd(": not found", STDERR_FILENO);
			ret = 1;
		}
	}
	return (ret);
}
