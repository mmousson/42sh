/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_must_skip_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:54:56 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/18 15:28:21 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_cmd_whitespace(const char c)
{
	return (c == ' ' || c == '\t' || c == '\"' || c == '\'');
}

int			hist_must_skip_cmd(const char *line)
{
	int	i;

	i = 0;
	while (is_cmd_whitespace(line[i]))
		i++;
	if (ft_strnequ(line + i, "fc", 2) && is_cmd_whitespace(line[i += 2]))
	{
		while (42)
		{
			while (is_cmd_whitespace(line[i]))
				i++;
			if (line[i] == '-')
			{
				while (!is_cmd_whitespace(line[i]))
				{
					if (line[i] == 's' || line[i] == 'e')
						return (1);
					i++;
				}
			}
			else
				return (1);
		}
	}
	return (0);
}
