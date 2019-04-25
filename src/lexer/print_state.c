/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:50:35 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/08 14:15:14 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lex.h"
#include <stdlib.h>
#include <unistd.h>

void			ft_print_stat_fd(int stat, int fd)
{
	static char	*tabl[20] = {
		"Start", "Char", "Int", "Space", "<", ">", "Double Quote",
		"Simple Quote", "&", "Back Slash", "$", "~", "|", "Silent Double Quote",
		"Silent Quote", "END", "VALIDATE", "VALIDATE STAR", "More",
		"Silent Validator"};

	if (stat >= 20 || stat < 0)
		ft_putnbr_fd(stat, fd);
	else
		ft_putstr_fd(tabl[stat], fd);
}

void			ft_print_ch_fd(int ch, int fd)
{
	static char	*tabl[17] = {
		"Start", "Char", "Int", "Space", "<", ">", "Double Quote",
		"Simple Quote", "&", "Back Slash", "$", "~", "|", "Semicolomn",
		"DASH", "SLASH", "NEW LINE"};

	if (ch >= 17 || ch < 0)
		ft_putnbr_fd(ch, fd);
	else
		ft_putstr_fd(tabl[ch], fd);
}

void			ft_print_ch_hash(int ch)
{
	static char	*tabl[17] = {
		"ZER", "CHA", "INT", "SPA", "REL", "RER", "DQT",
		"SQT", "ESP", "BSL", "DOL", "TIL", "PIP", "SMC",
		"DAS", "SLA", "NWL"};

	if (ch >= 17 || ch < 0)
		ft_putnbr(ch);
	else
		ft_putstr(tabl[ch]);
}

void			ft_step_lex(t_stat *stat)
{
	ft_print_stat_fd(stat->old_status, 1);
	ft_putchar('(');
	ft_print_ch_fd(stat->ch, 1);
	ft_putchar(')');
	ft_putchar_fd('-', 1);
	ft_print_stat_fd(stat->status, 1);
	while (read(0, NULL, 1) == 0);
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
