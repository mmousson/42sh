/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:33:37 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/31 22:14:20 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_42_H
# define SH_42_H

# include <termios.h>

# define SH_NAME	"42sh"
# define ALIAS_FILE "/.42sh_aliases"
# define HIST_FILE "/.42sh_history"

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

/*
**	Structure used to declare an array of function pointers associated with
**	specfic string
**
**	name -> String associated with the corresponding function pointer
**	handler -> The actual function pointer
*/

typedef struct		s_builtins
{
	char			*name;
	int				(*handler) (int argc, char **argv, char ***env);
}					t_builtins;

# define FILETYPE_DIRECTORY 1
# define FILETYPE_REGULAR 2
# define HASH_POWER 31
# define HASH_MOD 2731

# define INVALID_OPTION 2
# define SH_OPTS "c"
# define C_OPTION_OFFSET 0

/*
**	Structure representing an element of the shell's hashtable
**
**	hits -> The number of times the command was used since it was added to the
**		hashtable
**	full_path -> The absolute path to the utility
**	next -> Next element in case of collisions
*/

typedef struct		s_hash
{
	int				hits;
	char			*utility_name;
	char			*full_path;
	struct s_hash	*next;
}					t_hash;

/*
**
*/

typedef struct		s_vars
{
	char			*name;
	char			*value;
	struct s_vars	*prev;
	struct s_vars	*next;
}					t_vars;

/*
**	Define flags to interact with the 'core_spec_var_setget' function defined
**	in 'core/core_special_params.c'
**	SET (0) -> Modify the variable
**	GET (1) -> Return the variable's value without affecting it
*/

# define SET 0
# define GET 1

/*
**	Special Variables structure used to match an integer ID with an
**	actual value
*/

typedef struct		s_special_vars
{
	int				id;
	char			*value;
}					t_special_vars;

/*
**	Enum type to give us an more readable way of interacting with the
**	shell's Internal Variables
*/

typedef enum		e_special_var_id
{
	SPEC_0 = 0,
	SPEC_1 = 1,
	SPEC_2 = 2,
	SPEC_3 = 3,
	SPEC_4 = 4,
	SPEC_5 = 5,
	SPEC_6 = 6,
	SPEC_7 = 7,
	SPEC_8 = 8,
	SPEC_9 = 9,
	SPEC_QUESTION = 10,
	SPEC_DOLLAR = 11,
	SPEC_UNDERSCORE = 14,
	SPEC_EXCLAMATION = 15
}					t_special_var_id;

/*
**	g_builtins[] -> defined in utility/builtins_utility.c
*/

extern t_vars		*g_shell_var_list;
extern t_vars		*g_shell_tmp_vars;
extern t_alias		*g_alias_list;
extern t_builtins	g_builtins[];
extern t_hash		g_hash[HASH_MOD];

/*
**	==================== Main functions ====================
**
**	init_hash_table -> builtins/hash.c
**	hash_string -> utility/hash_string.c
**	add_hash_entry -> builtins/hash/add_hash_entry.c
**	alias_init -> utility/alias_init.c
**	is_builtin -> utility/builtins_utilty.c
**	init_job_ctrl -> job_control/initialize.c
*/

int					init_alias(void);
void				init_hash_table(void);
int					init_job_ctrl(void);
int					hash_string(char *string);
int					hash_already_exists(int index, char *name);
void				hash_add_entry(int string_hash, char *utility_name,
	char *full_path);
char				*core_spec_var_setget(int id, char *new_value,
	int set_or_get);
int					core_hash_spec_var(char var);

/*
**	==================== BUILTIN functions ====================
**
**	alias -> builtins/alias.c
**	bg -> builtins/bg.c
**	cd -> builtins/cd.c
**	echo -> builtins/echo.c
**	ft_exit -> builtins/ft_exit.c
**	fc -> builtins/builtins_fc.c
**	fg -> builtins/fg.c
**	hash -> builtins/hash.c
**	jobs -> builtins/jobs.c
**	set -> builtins/set.c
**	type -> builtins/type.c
**	unalias -> builtins/unalias.c
**	history -> builtins/history.c
**  fc -> builtins/fc.c
*/

int					blt_alias(int argc, char **argv, char ***env);
int					blt_bg(int argc, char **argv, char ***env);
int					blt_cd(int argc, char **argv, char ***env);
int					blt_echo(int argc, char **argv, char ***env);
int					blt_export(int argc, char **argv, char ***env);
int					blt_exit(int argc, char **argv, char ***env);
int					blt_fc(int argc, char **argv, char ***env);
int					blt_fg(int argc, char **argv, char ***env);
int					blt_hash(int argc, char **argv, char ***env);
int					blt_jobs(int argc, char **argv, char ***env);
int					blt_set(int argc, char **argv, char ***env);
int					blt_unset(int argc, char **argv, char ***env);
int					blt_test(int argc, char **argv, char ***env);
int					blt_type(int argc, char **argv, char ***env);
int					blt_unalias(int argc, char **argv, char ***env);
int					blt_history(int argc, char **argv, char ***env);

/*
**	==================== UTILITY functions ====================
**
**	utility_array_shift -> utility/utility_array_shift.c
**	utility_file_exists -> utility/utility_file_exists.c
**	utility_free_shell_vars_list -> utility/utility_free_lists.c
**	utility_free_alias_list -> utility/utility_free_lists.c
**	search_utility -> utility/search_utility.c
**	duplicate_environ -> utility/duplicate_environ.c
**	get_user_home -> utility/get_user_home.c
**	add_entry_to_environ -> utility/utility_environ_utilities.c
**	write_alias_list_to_file -> utility/write_alias_list_to_file.c
**	utility_generate_tmp_filename -> utility/utility_generate_tmp_filename.c
**	utility_get_var -> utility/utility_get_var.c
**	utility_set_var -> utility/utility_set_var.c
**	internal_variable_exists -> utility/internal_variable_exists.c
**	utility_get_effective_user_name -> utility/utility_get_effective_username.c
*/

void				utility_array_shift(char **to_shift);
int					utility_file_exists(const char *path);
void				utility_free_alias_list(void);
void				utility_free_shell_vars_list(void);
char				*utility_search(char *name);
int					utility_is_builtin(char *name);
char				**utility_duplicate_environ(char **env);
char				*utility_get_user_home(void);
char				*utility_get_aliases_file_full_path(void);
void				utility_write_alias_list_to_file(void);
void				utility_add_entry_to_environ(char ***environ, char *key,
	char *value);
int					utility_rm_entry_from_environ(char ***environ, char *key);
char				*utility_generate_tmp_filename(void);
char				*utility_generate_filename(void);
char				*utility_get_env_var(char ***environ, char *key);
int					utility_get_environ_length(char **tab);
void				utility_add_internal_var(char *name, char *value);
void				utility_add_tmp_var(char *name, char *value);
void				utility_flush_tmp_vars(void);
char				*utility_get_param(char *key, char **env);
char				*utility_get_var(char *name, char **env);
void				utility_set_var(char *name, char *value, char ***env,
	int export_var);
void				utility_delete_var(char *name, char ***env);
char				*utility_internal_var_exists(char *name, t_vars **holder);

#endif
