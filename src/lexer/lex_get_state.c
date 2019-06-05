/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:03:08 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/03 23:36:03 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int				lex_get_next_state(int state, int ch)
{
	static int	mat[NB_STATE][NB_CH] = {
		{EN, CH, SP, RL, RR, SK, SK, SK, ES, BS, PI, VA, US, ML, SD},
		{VS, CH, VS, VS, VS, SK, SK, SK, VS, BS, VS, VS, VS, VS, SD},
		{VS, VS, SP, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS, VS},
		{VS, VS, VS, RL, VS, VS, VS, VS, VO, VS, VS, VS, VS, VS, VS},
		{VS, VS, VS, VS, RR, VS, VS, VS, VO, VS, VS, VS, VS, VS, VS},
		{MO, DQ, DQ, DQ, DQ, US, DQ, DQ, DQ, DB, DQ, DQ, DQ, ML, SD},
		{MO, SQ, SQ, SQ, SQ, SQ, US, SQ, SQ, SQ, SQ, SQ, SQ, SQ, SQ},
		{MO, PS, PS, PS, PS, SK, SK, SK, PS, PS, PS, PS, US, ML, SD},
		{VS, VS, VS, VS, RR, VS, VS, VS, VA, VS, VS, VS, VS, VS, VS},
		{MO, CH, CH, CH, CH, CH, CH, CH, CH, CH, CH, CH, CH, CH, CH},
		{VS, VS, VS, VS, VS, VS, VS, VS, VS, VS, VA, VS, VS, VS, VS},
	};

	if (state >= NB_STATE || state < 0 || ch >= NB_CH || ch < 0)
		return (-1);
	return (mat[state][ch]);
}
