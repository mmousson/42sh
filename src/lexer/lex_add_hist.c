/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_add_hist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 19:30:07 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 20:48:53 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "history.h"

void		lex_add_hist(char **str, int status)
{
	if (lex_exclam(str))
		ft_putendl(*str);
	hist_update(*str, status);
}
