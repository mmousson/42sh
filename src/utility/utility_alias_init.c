/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 05:21:50 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/14 08:17:29 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "sh42.h"

t_alias		*alias_list = NULL;

/*
**	This functions get the substring of the read line starting at index 0
**	and until the first '=' sign
*/

static char	*ft_detach_token(char *line)
{
	int	token_len;

	token_len = 0;
	while (line[token_len] != '\0' && line[token_len] != '=')
		token_len++;
	return (ft_strsub(line, 0, token_len));
}

/*
**	Once a line has been read in the .42_aliases file, add it to the list
**	This function parses the line so the 'token' element contains the line
**	before the '=' sign and the 'replacement' element contains the rest
*/

static int	ft_fill_link(char *line)
{
	t_alias	*tmp;
	size_t	token_len;

	if ((tmp = ft_memalloc(sizeof(t_alias))) == NULL)
	{
		ft_putendl_fd("42sh: Internal malloc error", STDERR_FILENO);
		return (-1);
	}
	tmp->token = ft_detach_token(line);
	token_len = ft_strlen(tmp->token);
	tmp->replacement = ft_strsub(line, token_len + 1,
		ft_strlen(line + token_len + 1));
	if (tmp->replacement == NULL)
	{
		ft_putendl_fd("42sh: Internal malloc error", STDERR_FILENO);
		return (-1);
	}
	tmp->next = alias_list;
	alias_list = tmp;
	return (0);
}

/*
**	Initializes the alias list on program's bootup
**
**	Arguments: NONE
**
**	Return Value:
**	0 -> An error occured
**	1 -> Everything went well
*/

int			alias_init(void)
{
	int		fd;
	char	*line;

	if ((line = get_aliases_file_full_path()) == NULL)
		return (0);
	fd = open(line, O_CREAT | O_RDONLY, 0644);
	ft_strdel(&line);
	if (fd != -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (line == NULL || ft_fill_link(line) == -1)
			{
				free_alias_list();
				ft_strdel(&line);
				close(fd);
				return (0);
			}
			ft_strdel(&line);
		}
		close(fd);
		return (1);
	}
	ft_putendl_fd("Error opening ~/.42sh_aliases", 2);
	return (0);
}
