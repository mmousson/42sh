/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_store_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 09:35:49 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/29 09:38:26 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int		error_ep_or_ec(char close, t_stat *stat)
{
	if (close == '}')
		stat->status = EC;
	else
		stat->status = EP;
	return (-1);
}
