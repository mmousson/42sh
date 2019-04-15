/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:10:42 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/15 23:19:13 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

t_hash	g_hash[HASH_MOD];

static int	purge_hash_table(void)
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
	return (0);
}

static void	display_message_if_needed(int *witness, int target, char *msg)
{
	if (*witness == target)
		ft_putendl(msg);
	*witness = 1;
}

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
			display_message_if_needed(&witness, 0, "hits\tcommand");
			while (current)
			{
				format_infos(current);
				current = current->next;
			}
		}
	}
	display_message_if_needed(&witness, 0, "hash: hash table is empty");
	return (0);
}

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
		if (ft_strequ("--", argv[1]))
			option_on = 0;
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
