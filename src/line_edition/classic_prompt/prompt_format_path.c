/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_format_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 07:44:11 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/04 12:13:13 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "line_edition.h"

/*
**
*/

void	prompt_format_path(char *path)
{
	char	*catch;

	if (path == NULL)
		return ;
	if ((catch = ft_strrchr(path, '/')) != NULL)
	{
		catch = ft_strsub(path, 0, catch - path + 1);
		ft_putstr(catch);
		ft_putstr(WHITE_BOLD);
		ft_putstr(path + ft_strlen(catch));
		ft_strdel(&catch);
	}
	else
		ft_putstr(path);
}
