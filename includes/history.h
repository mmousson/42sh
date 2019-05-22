/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:08:21 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/22 13:48:11 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HISTORY_H
# define _HISTORY_H

# include "line_edition.h"

char				*hist_parsline(char *line);
void				hist_add(char *str);
void				hist_init(void);
void				hist_update(char *line);
char				*hist_getexpend(char **str);

/*
**	search
*/

int					hist_search(char *str, int ret);
void				hist_searchline(void);
int					hist_lst(char *str, int ret);

/*
**	alloc
*/

void				hist_alloc_search(t_prompt prompt);
void				hist_addstr(char *str);
void				hist_delchar(void);
void				hist_addline(char *line, int forwards);

/*
**	utils
*/

int					hist_strstr(char *haystack, char *needle);

#endif
