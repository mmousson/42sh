/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:33:37 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/14 08:16:45 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_42_H
# define SH_42_H

# include <termios.h>

# define ALIAS_FILE "/.42sh_aliases"

/*
**	Structure representing the alias list in the current shell execution
**	environment
**	Said list is read and parsed from the file '.42sh_aliases' in the user's
**	HOME directory when the shell boots up
**	Then the list can be updated during execution using the 'alias'
**	and 'unalias' BUILTIN utlities declared below
*/

typedef struct		s_alias
{
	char			*token;
	char			*replacement;
	struct s_alias	*next;
}					t_alias;

extern t_alias		*alias_list;

/*
**	==================== Main functions ====================
**
**	alias_init -> utility/alias_init.c
**	free_alias_list -> utility/free_alias_list.c
**	init_job_ctrl -> job_control/initialize.c
*/

int					alias_init(void);
void				free_alias_list(void);
int					init_job_ctrl(struct termios *bkp_conf);

/*
**	==================== BUILTIN functions ====================
**
**	bg -> builtins/bg.c
**	fg -> builtins/fg.c
**	jobs -> builtins/jobs.c
**	alias -> builtins/alias.c
**	unalias -> builtins/unalias.c
*/

int					bg(int argc, char **argv, char ***env);
int					fg(int argc, char **argv, char ***env);
int					jobs(int argc, char **argv, char ***env);
int					alias(int argc, char **argv, char ***env);
int					unalias(int argc, char **argv, char ***env);

/*
**	==================== UTILITY functions ====================
**
**	get_user_home -> utility/get_user_home.c
**	write_alias_list_to_file -> utility/write_alias_list_to_file.c
*/

char				*get_user_home(void);
char				*get_aliases_file_full_path(void);
void				write_alias_list_to_file(void);

#endif
