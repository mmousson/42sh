/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:33:37 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/07 11:33:38 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_42_H
# define SH_42_H

/*
**	==================== Main functions ====================
**
**	init_job_ctrl -> job_control/initialize.c
*/

int	init_job_ctrl(struct termios *bkp_conf);

#endif
