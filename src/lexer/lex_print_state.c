/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_print_state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:03:42 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/29 09:12:26 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lex.h"

void			ft_print_stat_fd(int stat, int fd)
{
	static char	*tabl[20] = {
		"Start", "Char", "Space", "<", ">", "Double Quote",
		"Simple Quote", "(", "&", "\\", "|",
		"STACKING", "Un STACKING", "Mini LEx", "Double quote + BS", "$",
		"VALIDATE", "VALIDATE STAR", "More", "SDollard"
	};

	if (stat >= 19 || stat < 0)
		ft_putnbr_fd(stat, fd);
	else
		ft_putstr_fd(tabl[stat], fd);
}

void			ft_print_ch_fd(int ch, int fd)
{
	static char	*tabl[17] = {
		"Start", "Char", "Space", "<", ">", "Double Quote",
		"Simple Quote", "PAO (", "&", "\\", "|", ";", "PAC )",
		"EXC !", "DOL $", "EXPAND"};

	if (ch >= 17 || ch < 0)
		ft_putnbr_fd(ch, fd);
	else
		ft_putstr_fd(tabl[ch], fd);
}

void			ft_print_ch_hash(int ch)
{
	static char	*tabl[17] = {
		"ZER", "CHA", "SPA", "REL", "RER", "DQT", "SQT",
		"ESP", "BSL", "PIP", "SMC", "PAC", "EXC",
		"DOL", "EXP"
	};

	if (ch >= 17 || ch < 0)
		ft_putnbr(ch);
	else
		ft_putstr(tabl[ch]);
}

void			ft_print_token(t_tok *tok)
{
	int			k;

	k = 0;
	tok = tok->next;
	while (tok)
	{
		ft_putstr("{[");
		ft_putstr(tok->content);
		ft_putstr("] (");
		ft_print_ch_fd(tok->status, 1);
		ft_putstr(":");
		ft_putnbr(tok->status);
		ft_putstr(")}   ");
		tok = tok->next;
		k++;
		if (!(k % 3))
			ft_putchar('\n');
	}
	ft_putchar('\n');
}
