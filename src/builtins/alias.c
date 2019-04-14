/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 23:09:33 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/14 06:06:23 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

/*
**	This function works like the one below, except that it will loop through
**	the entire alias list and display every existing definition in the current
**	shell execution environment
**
**	Arguments: NONE
**
**	Return Value: Always ALIAS_OK (0)
*/

static int	display_all_aliases(void)
{
	t_alias	*local;

	local = alias_list;
	while (local)
	{
		ft_putstr("alias ");
		ft_putstr(local->token);
		ft_putstr("=\'");
		ft_putstr(local->replacement);
		ft_putstr("\'\n");
		local = local->next;
	}
	return (ALIAS_OK);
}

/*
**	This function is called to display a particular alias definition
**	or an error message if said definition doesn't exist
**
**	Arguments:
**	tmp -> The alias definition identifier (token)
**
**	Return Value:
**	ALIAS_OK (0) -> Everythinf went well
**	ALIAS_ERROR (1) -> An error occured
*/

static int	display_alias_definition(char *tmp)
{
	t_alias	*local;

	local = alias_list;
	while (local)
	{
		if (ft_strequ(tmp, local->token))
		{
			ft_putstr("alias ");
			ft_putstr(local->token);
			ft_putstr("=\'");
			ft_putstr(local->replacement);
			ft_putstr("\'\n");
			return (ALIAS_OK);
		}
		local = local->next;
	}
	ft_putstr_fd("42sh: alias: ", STDERR_FILENO);
	ft_putstr_fd(tmp, STDERR_FILENO);
	ft_putendl_fd(": not found", STDERR_FILENO);
	return (ALIAS_ERROR);
}

/*
**	This function creates a new 't_alias' link, populates it, and makes it the
**	new head of the existing alias list
**
**	Arguments:
**	key -> The string representing the alias to be treated
**	tmp -> The sub-string of 'key' representing only its identifier (token)
**
**	Return Value:
**	ALIAS_OK (0) -> Everythinf went well
**	ALIAS_ERROR (1) -> An error occured
*/

static int	add_alias(char *key, char *tmp)
{
	t_alias	*new;

	if ((new = ft_memalloc(sizeof(t_alias))) == NULL)
		return (ALIAS_ERROR);
	new->token = tmp;
	if ((new->replacement = ft_strdup(key + ft_strlen(tmp))) == NULL)
	{
		ft_strdel(&tmp);
		ft_memdel((void **)&(new));
		return (ALIAS_ERROR);
	}
	new->next = alias_list;
	alias_list = new;
	return (ALIAS_OK);
}

/*
**	This function checks a string (extracted from the buitin's arguments)
**	and select the correct function to treat it dependding on its content
**	First case:
**		If there are no '=' sign in the argument, then it means the user
**		just passed an alias name, so just print its definition
**		(display_alias_definition)
**	Second case:
**		The alias key (as in, the text before the first '=' sign) corresponds
**		to an already existing alias definition in the existing list
**		Then, just update said definition (if statement in while loop)
**	Third case:
**		The alias doesn'y already exist, then create it and make it the new
**		head of the existing list (add_alias function)
**
**	Arguments:
**	key -> The string representing the alias to be treated
**
**	Return Value:
**	ALIAS_OK (0) -> Everythinf went well
**	ALIAS_ERROR (1) -> An error occured
*/

static int	check_key(char *key)
{
	t_alias		*local;
	ptrdiff_t	ptr_dist;
	char		*tmp;

	if ((tmp = ft_strrchr(key, '=')) == NULL)
		return (display_alias_definition(key));
	ptr_dist = (ptrdiff_t)tmp - (ptrdiff_t)key;
	if ((tmp = ft_strsub(key, 0, ptr_dist)) == NULL)
		return (ALIAS_ERROR);
	local = alias_list;
	while (local)
	{
		if (ft_strequ(tmp, local->token))
		{
			ft_strdel(&(local->replacement));
			local->replacement = ft_strdup(key + ft_strlen(tmp) + 1);
			ft_strdel(&tmp);
			return (ALIAS_OK);
		}
		local = local->next;
	}
	return (add_alias(key, tmp));
}

/*
**	============================= BUITLIN COMMAND =============================
**	Main function for the 'alias' utility function
**	If no option is found, check that we receive precisely one argument
**	and that the first argument (the 'key') only contains valid characters for
**	parsing
**	If not, we display an appropriate error message on the Standard Error
**
**	Once all tests have been passed, we update the alias list
**	First, we try, to replace an already existing alias
**	If it does not already exist, the 'replace_alias' function will
**	return (ALIAS_NEW)
**	In this case, all we need to do is to append the alias definition to the
**	current alias list
**
**	Return Value:
**	ALIAS_OK (0) -> Everythinf went well
**	ALIAS_ERROR (1) -> An error occured
*/

int	alias(int argc, char **argv, char ***env)
{
	int		ret;

	ret = 0;
	(void)env;
	if (argc == 1)
		return (display_all_aliases());
	while (--argc > 0)
	{
		argv++;
		ret = (check_key(argv[0]) || ret) ? ALIAS_ERROR : ALIAS_OK;
	}
	write_alias_list_to_file();
	return (ret);
}
