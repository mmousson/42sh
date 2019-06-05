/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_alias_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 05:21:50 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/05 09:33:23 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "sh42.h"

t_alias		*g_alias_list = NULL;

/*
**	Function to tell the user that an alias is badly formatted and therefore
**	ignored
**
**	Arguments:
**	line -> The alias definition we read that is badly formatted
**
**	Return Value: Always 0 (will be used as return val by the calling function)
*/

static int	notify_bad_alias(t_alias *tmp, const char *line)
{
	ft_putstr_fd("42sh: WARNING: '", STDERR_FILENO);
	ft_putstr_fd(line, STDERR_FILENO);
	ft_putendl_fd("' alias definition is badly formatted (ignored)", 2);
	ft_memdel((void **)&(tmp));
	return (0);
}

/*
**	This functions get the substring of the read line starting at index 0
**	and until the first '=' sign
*/

static char	*ft_detach_token(const char *line)
{
	int	token_len;

	token_len = 0;
	while (line[token_len] != '\0' && line[token_len] != '=')
		token_len++;
	if (line[token_len] == '\0')
		return (NULL);
	return (ft_strsub(line, 0, token_len));
}

/*
**	Once a line has been read in the .42_aliases file, add it to the list
**	This function parses the line so the 'token' element contains the line
**	before the '=' sign and the 'replacement' element contains the rest
*/

static int	ft_fill_link(const char *line)
{
	t_alias	*tmp;
	size_t	token_len;

	if ((tmp = ft_memalloc(sizeof(t_alias))) == NULL)
	{
		ft_putendl_fd("42sh: Internal malloc error", STDERR_FILENO);
		return (-1);
	}
	if ((tmp->token = ft_detach_token(line)) == NULL)
		return (notify_bad_alias(tmp, line));
	token_len = ft_strlen(tmp->token);
	tmp->replacement = ft_strsub(line, token_len + 1,
		ft_strlen(line + token_len + 1));
	if (tmp->replacement == NULL)
	{
		ft_putendl_fd("42sh: Internal malloc error", STDERR_FILENO);
		return (-1);
	}
	tmp->next = g_alias_list;
	g_alias_list = tmp;
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

int			init_alias(void)
{
	int		fd;
	char	*line;

	if ((line = utility_get_aliases_file_full_path()) == NULL)
		return (0);
	fd = open(line, O_CREAT | O_RDONLY, 0644);
	ft_strdel(&line);
	if (fd != -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (line == NULL || ft_fill_link(line) == -1)
			{
				utility_free_alias_list();
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
