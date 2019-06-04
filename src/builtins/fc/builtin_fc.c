/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:47:35 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/31 17:47:35 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

/*
**
*/

int			blt_fc(int argc, char **argv, char ***env)
{
	t_options_infos	*inf;

	if ((inf = blt_fc_parse_options(argc, argv, *env)) == NULL)
		return (2);
	if (inf->editor_name == NULL)
	{
		if ((inf->editor_name = ft_strdup("/bin/ed")) == NULL)
		{
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
			return (2);
		}
	}
	argc -= inf->parsed;
	argv += inf->parsed;
	blt_fc_read_args(argc, argv, inf);
	blt_fc_set_default_values(inf);
	return (0);
}