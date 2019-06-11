/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:10:42 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/11 16:29:00 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

t_hash	g_hash[HASH_MOD];

/*
**	Function to format the informations held in a cell of the hashtable
**	Infos will be formatted in this way: %4d	%s, hits, full_path
**
**	Arguments:
**	current -> The hashtable's cell from which we will format the informations
**
**	Return Value: NONE
*/

static void	format_infos(t_hash *current)
{
	int	pad;
	int	mag;

	pad = 0;
	mag = ft_order_of_magnitude(current->hits);
	while (++pad < mag)
		ft_putchar(' ');
	ft_putnbr(current->hits);
	ft_putchar('\t');
	ft_putendl(current->full_path);
}

/*
**	Loop through all index og the hashtable, and if there are something in
**	the current index, display its content
**
**	Arguments: NONE
**
**	Return Value: Always HASH_OK (0)
*/

static int	display_table(void)
{
	int		i;
	int		witness;
	t_hash	*current;

	i = -1;
	witness = 0;
	while (++i < HASH_MOD)
	{
		if (g_hash[i].full_path != NULL)
		{
			current = &(g_hash[i]);
			if (!witness++)
				ft_putendl("hits\tcommand");
			while (current)
			{
				format_infos(current);
				current = current->next;
			}
		}
	}
	if (!witness)
		ft_putendl("hash: hash table is empty");
	return (HASH_OK);
}

/*
**	This function parses the option(s) in a POSIX-compliant way
**	The double hyphen "--" stops the parsing and breaks the loop
**	In this builtin, we don't need to return a structure or anything like
**	that, because the only supported option (-r) doesn't affect the behaviour
**	of the utility
**	We just need to return whther or not a problem occured
**
**	Arguments:
**	ac -> A pointer to the argument counter of the main function
**	av -> A pointer to the arguments array of the main function
**
**	Return Value:
**	1  -> Everything went well
**	-1 -> Unsupported option detected
*/

static int	parse_options(int *ac, char ***av)
{
	int		i;

	while (*ac > 1 && (*av)[1][0] == '-')
	{
		i = 0;
		(*ac)--;
		(*av)++;
		if (ft_strequ((*av)[0], "--"))
			break ;
		while ((*av)[0][++i] != '\0')
		{
			if ((*av)[0][i] == 'r')
				utility_purge_hash_table();
			else
			{
				ft_putstr_fd("42sh: hash: -", STDERR_FILENO);
				ft_putchar_fd((*av)[0][i], STDERR_FILENO);
				ft_putendl_fd(": invalid option", STDERR_FILENO);
				return (-1);
			}
		}
	}
	return (1);
}

/*
**	============================= BUITLIN COMMAND =============================
**	Builtin command to handle the maintenance of the shell's hashtable
**	First parse the utility's options
**	Accepted option are:
**	"-r" -> Purge the table
**	Then, if no error occured, loop through all the remaining arguments and
**	add it the hashtable
**	If there are actual arguments, just display the content of the hashtable
**	in the form: %4d\t%s\n, hits, full_path
**
**	Return Value:
**	HASH_OK (0) -> Everything went well
**	HASH_ERROR (1) -> An error occured
*/

int			blt_hash(int argc, char **argv, char ***env)
{
	char	*tmp;

	(void)env;
	if (argc == 1)
		return (display_table());
	else if (parse_options(&argc, &argv) == -1)
		return (HASH_NO_SUCH_OPTION);
	while (argc > 1)
	{
		if ((tmp = utility_search(*env, argv[1])) == NULL)
		{
			ft_putstr_fd("42sh: hash: ", STDERR_FILENO);
			ft_putstr_fd(argv[1], STDERR_FILENO);
			ft_putendl_fd(": not found", STDERR_FILENO);
		}
		else
			ft_strdel(&tmp);
		argc--;
		argv++;
	}
	return (0);
}
