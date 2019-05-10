/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:52:20 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/10 11:19:44 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				auto_completion(char *str, int ret)
{
	if (str[0] == '\t' && ret == 1)
	{
		if (auto_isblank())
			line_paste("    ", g_env.count);
		else if (g_data.status)
			return (auto_choose());
		else
		{
			auto_filldata();
			return (auto_printword());
		}
	}
	else
		return (0);
	return (1);
}
