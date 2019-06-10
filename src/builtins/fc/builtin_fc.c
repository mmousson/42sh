/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:47:35 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/10 16:53:18 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

int			blt_fc(int argc, char **argv, char ***env)
{
	int				ret;
	t_options_infos	*inf;

	if ((inf = blt_fc_parse_options(argc, argv, *env)) == NULL
		|| inf->invalid)
		return (2);
	argc -= inf->parsed;
	argv += inf->parsed;
	blt_fc_read_args(argc, argv, inf);
	blt_fc_set_default_values(inf);
	blt_fc_extract(inf);
	if (inf->dash_s != NULL)
		ret = blt_fc_reinvoke(inf, env);
	else if (inf->listing)
		ret = blt_fc_list(inf);
	else
		ret = blt_fc_edit_and_reinvoke(inf, env);
	blt_fc_free_memory(inf);
	return (ret);
}
