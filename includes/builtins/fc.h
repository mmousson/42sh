/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 21:04:39 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/31 21:04:39 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FC_H
# define FC_H

# include <inttypes.h>
# include "libft.h"
# include "line_edition.h"

# define SWITCH 0
# define GET_EDITOR 1
# define FILL 2

/*
**
*/

typedef struct	s_offset_matcher
{
	char		letter;
	size_t		offset;
	uint8_t		must_switch;
}				t_offset_matcher;

/*
**
*/

typedef struct	s_reinvoke
{
	char		*old;
	char		*new;
}				t_reinvoke;

/*
**	Structure holding everything we need to know about the options of the
**	fc builtin utility
**
**	options -> 
**	parsed -> 
**	editor_name ->
*/

typedef struct	s_options_infos
{
	int			ret;
	int			parsed;
	uint8_t		invalid;
	uint8_t		reversed;
	uint8_t		suppressed;
	uint8_t		listing;
	char		*editor_name;
	char		*first;
	char		*last;
	t_reinvoke	*dash_s;
	t_history	*from;
	t_history	*to;
}				t_options_infos;

/*
**
*/

t_options_infos	*blt_fc_parse_options(int argc, char **argv, char **env);
void			blt_fc_read_args(int argc, char **argv, t_options_infos *inf);
void			blt_fc_set_default_values(t_options_infos *inf);
void			blt_fc_extract(t_options_infos *inf);
int				blt_fc_reinvoke(t_options_infos *inf);
int				blt_fc_list(t_options_infos *inf);
int				blt_fc_edit_and_reinvoke(t_options_infos *inf, char ***env);
void			blt_fc_free_memory(t_options_infos *inf);

#endif
