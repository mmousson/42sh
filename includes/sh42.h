/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:33:37 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/14 15:19:40 by mmousson         ###   ########.fr       */
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

typedef struct		s_builtins
{
	char			*name;
	int				(*handler) (int argc, char **argv, char ***env);
}					t_builtins;

# define HASH_POWER 31
# define HASH_MOD 2731

typedef struct		s_hash
{
	char			*full_path;
	struct s_hash	*next;
}					t_hash;

extern t_alias		*alias_list;
extern t_builtins	g_builtins[];
extern t_hash		g_hash[HASH_MOD];

/*
**	==================== Main functions ====================
**
**	init_hash_table -> builtins/hash.c
**	alias_init -> utility/alias_init.c
**	free_alias_list -> utility/free_alias_list.c
**	is_builtin -> utility/builtins_utilty.c
**	init_job_ctrl -> job_control/initialize.c
*/

void				init_hash_table(void);
int					alias_init(void);
void				free_alias_list(void);
int					is_builtin(char *name);
int					init_job_ctrl(struct termios *bkp_conf);

/*
**	==================== BUILTIN functions ====================
**
**	alias -> builtins/alias.c
**	bg -> builtins/bg.c
**	cd -> builtins/cd.c
**	echo -> builtins/echo.c
**	ft_exit -> builtins/ft_exit.c
**	fg -> builtins/fg.c
**	hash -> builtins/hash.c
**	jobs -> builtins/jobs.c
**	type -> builtins/type.c
**	unalias -> builtins/unalias.c
*/

int					alias(int argc, char **argv, char ***env);
int					bg(int argc, char **argv, char ***env);
int					cd(int argc, char **argv, char ***env);
int					echo(int argc, char **argv, char ***env);
int					ft_exit(int argc, char **argv, char ***env);
int					fg(int argc, char **argv, char ***env);
int					hash(int argc, char *8argv, char ***env);
int					jobs(int argc, char **argv, char ***env);
int					type(int argc, char **argv, char ***env);
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
