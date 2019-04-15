/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:10:42 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 01:15:43 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

t_hash	g_hash[HASH_MOD];

/*
**	This function will loop through the entire hashtable and clear every link
**	of every list of every occupied cell of the table, as well as free the
**	allocated memory occupied by excess elements
**
**	Arguments: NONE
**
**	Return Value: NONE
*/

static void	purge_hash_table(void)
{
	int		i;
	int		not_base;
	t_hash	*current;
	t_hash	*next;

	i = -1;
	while (++i < HASH_MOD)
	{
		if (g_hash[i].full_path != NULL)
		{
			not_base = 0;
			current = &(g_hash[i]);
			while (current)
			{
				next = current->next;
				current->hits = 0;
				ft_strdel(&(current->full_path));
				if (not_base)
					ft_memdel((void **)&(current));
				current = next;
				not_base = 1;
			}
		}
	}
}

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
			if (!witness)
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

int			hash(int argc, char **argv, char ***env)
{
	int		option_on;
	char	*tmp;

	(void)env;
	option_on = 1;
	if (argc == 1)
		return (display_table());
	while (argc > 1)
	{
		ft_strequ("--", argv[1]) ? option_on = 0 : (0);
		else if (ft_strequ("-r", argv[1]) && option_on)
			purge_hash_table();
		else if ((tmp = search_utility(argv[1])) == NULL)
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
