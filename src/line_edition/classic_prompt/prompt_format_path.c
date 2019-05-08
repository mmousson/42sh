/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_format_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 07:44:11 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/06 19:47:38 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "prompt.h"

/*
**	Prints the current path, truncated to a maximum dpeth of 3 by the function
**	'ft_trim_path' in the file 'prompt_classic.c'
**	If the resulting path contains at least ine slash(es), then the last folder
**	is printed with a bold font
**	The size of the resulting path is then returned
**
**	Arguments:
**	path -> The truncated path returned by the function 'ft_trim_path'
**
**	Return Value:
**	The actual size-on-screen of the printed path
*/

int	prompt_format_path(char *path)
{
	char	*catch;

	if (path == NULL)
		return (0);
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
	return (ft_strlen(path));
}
