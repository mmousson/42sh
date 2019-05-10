/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:03:08 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/10 10:26:56 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#define NB_SPLIT_MAT 17

int				lex_get_other_part(int state, int ch)
{
	static int mat[NB_STATE][NB_CH - NB_SPLIT_MAT] = {
		{CH, CH},
		{CH, CH},
		{CH, CH},
		{VS, VS},
		{VS, VS},
		{VS, VS},
		{DQ, DQ},
		{SQ, SQ},
		{VS, VS},
		{CH, CH},
		{PS, EP},
		{CH, CH},
		{VS, VS},
		{PD, EP},
		{EP, CP},
		{EP, VA},
	};

	if (state >= NB_STATE || state < 0 || ch >= NB_CH - NB_SPLIT_MAT || ch < 0)
		return (-1);
	return (mat[state][ch]);
}

int				lex_get_next_state(int state, int ch)
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
		{VS, DO, DO, VS, VS, VS, VS, VS, VS, VS, VA, VS, VS, VS, DO, VS, EP},
		{VS, CH, CH, VS, VS, VS, DS, SS, VS, BS, VS, CH, VS, VS, CH, VS, VS},
		{VS, VS, VS, VS, VS, VS, VS, VS, VS, BS, VS, VS, VA, VS, VS, VS, VS},
		{EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP},
		{EP, PD, PD, PD, PD, PD, PD, PD, PD, PD, PD, PD, PD, PD, PD, PD, EP},
		{EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP, EP},
	};

	if (state >= NB_STATE || state < 0 || ch >= NB_CH || ch < 0)
		return (-1);
	else if (ch >= NB_SPLIT_MAT)
		return (lex_get_other_part(state, ch - NB_SPLIT_MAT));
	return (mat[state][ch]);
}
