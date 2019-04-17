/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 21:18:12 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/04 14:38:04 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexpars.h"
#include "line_edition.h"
#include <stdlib.h>

int			ft_ctrld_quote(t_args *args, char *fus, int prompt)
{
	char	*tmp;

	if (args->line->ctrld)
	{
		if (!fus || (fus && !fus[0]))
		{
			ft_putstr_fd("21sh: unexpected EOF\n", 2);
			ft_quit(args);
			return (-2);
		}
	}
	else
	{
		if (prompt != PPIPE)
		{
			if (!(tmp = ft_strjoin(args->str, "\n")))
				return (1);
			free(args->str);
			args->str = tmp;
		}
	}
	return (0);
}

int			ft_quote(t_args *args, int prompt)
{
	char	*fus;
	char	*tmp;
	int		ret;

	fus = NULL;
	while (!fus)
	{
		if ((ret = ft_ctrld_quote(args, fus, prompt)))
			return (ret);
		fus = ft_get_line(args->line, prompt, NULL);
		if (!(tmp = ft_strjoin(args->str, fus)))
			return (1);
		free(args->str);
		args->str = tmp;
	}
	if (fus)
	{
		free(fus);
		fus = NULL;
	}
	args->charac = SPACE;
	args->k--;
	return (0);
}

int			ft_dbqt(t_args *args)
{
	if (!args->line->isatty)
	{
		ft_putstr_fd("21sh: unexpected EOF", 2);
		ft_putstr_fd(" while looking for matching `\"'\n", 2);
		ft_exit_clean_args(args, 1);
	}
	return (ft_quote(args, PDQUOTE));
}

int			ft_spqt(t_args *args)
{
	if (!args->line->isatty)
	{
		ft_putstr_fd("21sh: unexpected EOF", 2);
		ft_putstr_fd(" while looking for matching `\''\n", 2);
		ft_exit_clean_args(args, 1);
	}
	return (ft_quote(args, PQUOTE));
}

int			ft_more_pipe(t_args *args)
{
	if (!args->line->isatty)
	{
		ft_putstr_fd("21sh: syntaxe error: unexpected EOF\n", 2);
		ft_exit_clean_args(args, 1);
	}
	return (ft_quote(args, PPIPE));
}
