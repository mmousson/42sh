/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:12:37 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/10 14:13:22 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int				ft_get_next_state(int state, int ch)
{
	static int	mat[NB_STATE][NB_CH] = {
		{EN, CH, IN, SP, RL, RR, DS, SS, ES, BS, DO, TI, PI, VA, CH, CH, VA},
		{VS, CH, CH, VS, VS, VS, DS, SS, VS, BS, VS, CH, VS, VS, CH, CH, VS},
		{VS, CH, IN, VS, VS, VS, DS, SS, VS, BS, VS, CH, VS, VS, CH, CH, VS},
		{VS, VS, VS, SP, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS},
		{VS, VS, VS, VS, VA, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS},
		{VS, VS, VS, VS, VS, VA, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS},
		{MO, DQ, DQ, DQ, DQ, DQ, SV, DQ, DQ, DQ, DQ, DQ, DQ, DQ, DQ, DQ, DQ}, 
		{MO, SQ, SQ, SQ, SQ, SQ, SQ, SV, SQ, SQ, SQ, SQ, SQ, SQ, SQ, SQ, SQ}, 
		{VS, VS, IN, VS, VS, VA, VS, VS, VA, VS, VS, CH, VS, VS, VA, VS, VS},
		{MO, CH, CH, CH, CH, CH, CH, CH, CH, CH, CH, CH, CH, CH, CH, CH, CH}, 
		{VS, DO, DO, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS, DO, VS, VS},
		{VS, CH, CH, VS, VS, VS, DS, SS, VS, BS, VS, CH, VS, VS, CH, VS, VS},
		{VS, VS, VS, VS, VS, VS, VS, VS, VS, BS, VS, VS, VA, VS, VS, VS, VS}
	};

	if (state >= NB_STATE || state < 0 || ch >= NB_CH || ch < 0)
		return (-1);
	return (mat[state][ch]);
}
