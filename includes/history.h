/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:08:21 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/13 20:20:12 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HISTORY_H
# define _HISTORY_H

# include "line_edition.h"

char				*hist_parsline(char *line);
void				hist_add(char *str);
void				hist_init(void);
void				hist_update(char *line);

#endif
