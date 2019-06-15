/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 07:36:36 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/15 17:24:46 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"
#include "pars.h"
#include "lex.h"
#include "libft.h"
#include "job_control_42.h"

static int	error_filename(char **file, char *path)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" Ambiguous redirect\n", 2);
	ft_del_words_tables(&file);
	g_current_ret = 1;
	return (-1);
}

int			expand_filename(char **path, t_tok *token, int red)
{
	char	**files;
	int		k;
	t_tok	*end;

	(void)red;
	end = token->next;
	if (!path || !(files = sh_glob(*path)))
		return (0);
	if (red && files[1])
		return (error_filename(files, *path));
	free(*path);
	*path = files[0];
	k = 0;
	while (files[++k])
	{
		token->next = new_token_space();
		token = token->next;
		token->next = new_token_char(files[k]);
		token = token->next;
	}
	free(files);
	token->next = end;
	return (0);
}
