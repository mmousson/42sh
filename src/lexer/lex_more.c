/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:56:57 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/04 15:59:36 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lex.h"
#include "libft.h"

static int		ft_nomatch(int status, char *fus)
{
	if (fus)
		free(fus);
	ft_putstr_fd("21sh: unexpected EOF while looking for matching `", 2);
	if (status == DQ)
		ft_putstr_fd("\"", 2);
	else if (status == SQ)
		ft_putstr_fd("'", 2);
	else
		ft_putstr_fd("|", 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

static int		get_prompt(int stat)
{
	static int	tab_stat[3] = {
		DQ, SQ, BS};
	static int	tab_prmt[3] = {
		PDQUOTE, PQUOTE, PBACKS};
	int			k;

	k = 0;
	while (k < 3)
	{
		if (stat == tab_stat[k])
			return (tab_prmt[k]);
		k++;
	}
	return (PDEF);
}

static int		ft_append_nl(char **str, int nl)
{
	char		*tmp;

	if (nl)
	{
		if (!(tmp = ft_strjoin(*str, "\n")))
			return (1);
		free(*str);
		*str = tmp;
	}
	return (0);
}

int				ft_more(t_stat *stat, char **str, int nl)
{
	char		*fus;
	char		*tmp;
	int			prompt;

	prompt = get_prompt(stat->old_status);
	fus = NULL;
	while (!fus)
	{
		fus = line_get_readline(prompt, NULL);
		if ((fus == NULL || fus[0] == 0) && g_env.ctrld)
			return (ft_nomatch(stat->old_status, fus));
		if (ft_append_nl(str, nl))
			return (0);
		if (!(tmp = ft_strjoin(*str, fus)))
			return (0);
		free(*str);
		*str = tmp;
	}
	if (fus)
		free(fus);
	stat->k--;
	stat->status = stat->old_status;
	return (1);
}
