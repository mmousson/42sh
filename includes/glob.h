/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:36:51 by akarasso          #+#    #+#             */
/*   Updated: 2019/06/11 13:06:10 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_H
# define GLOB_H

# include <stdlib.h>

# define GLO_STAR			0x01
# define GLO_QUEST			0x02
# define GLO_RANGE			0x04
# define GLO_CONST			0x08
# define GLO_SEPAR			0x10
# define GLO_HIDE			0x20

/*
** Glob Lexer
*/

typedef struct	s_globtok
{
	void				*data;
	struct s_globtok	*next;
	struct s_globtok	*prev;
}				t_globtok;

typedef struct	s_globlex
{
	t_globtok		*first;
	t_globtok		*last;
	unsigned int	len;
}				t_globlex;

/*
** Glob Main Struct
*/

typedef struct	s_glob
{
	int			depth;
	char		*root;
	size_t		root_len;
	char		*expr;
	char		**res;
	t_globlex	*lexer;
}				t_glob;

/*
** Substring Match Main Struct
*/

typedef struct	s_submatch
{
	int			suffix;
	int			greedy;
	char		*param;
	char		*word;
	t_globlex	*lexer;
}				t_submatch;

/*
** Glob Token Types
*/

typedef struct	s_strtab_token
{
	int			type;
	char		*value;
	char		**tab;
}				t_strtab_token;

typedef struct	s_rng_token
{
	int			type;
	char		*value;
	char		allow[256];
	char		negative;
}				t_rng_token;

typedef struct	s_chr_token
{
	int		type;
	char	value;
}				t_chr_token;

typedef struct	s_str_token
{
	int		type;
	char	*value;
	size_t	len;
}				t_str_token;

int				is_file_matching_pattern(t_globtok *tok, char *cmd);
int				check_matching_files(t_glob *gl, char **files);
int				read_directory(char ***files, char *path, int depth);
char			**get_files_to_match(t_glob *gl);
void			init_glob(t_glob *gl);
void			reset_glob(t_glob *gl);
char			**sh_glob(char *path);
void			globlexelemdel(t_globtok *tok);
void			globlexdel(t_globlex **container);
int				tokenize(t_glob *gl);
int				match_files(t_glob *gl);
int				is_matching_asterisk(t_globtok *tok, char *file);
int				is_matching_question(t_globtok *tok, char *file);
int				is_matching_const(t_globtok *tok, t_str_token *tkn, char *file);
int				is_matching_range(t_globtok *tok, t_rng_token *tkn, char *file);
int				is_matching_hidden(t_globtok *tok, t_chr_token *tkn,
																	char *file);
int				walk_range(char **beg);
void			parse_range(char *allow, char *s);
int				is_quote(int c);
size_t			expansion_unquote(char *str);
int				get_path_depth(char *path);
t_globtok		*globtok_last(t_globtok *lst);
unsigned int	globlexlen(t_globlex *container);
t_globlex		*globlexnew(void *content);
t_globtok		*globtoknew(void *data);
t_globtok		*globlex_pushback(t_globlex *container, void *data);
int				slice_path(t_glob *gl, char *path);
void			walk_quote(char **str);
void			walk_word(char **s);
t_rng_token		*glob_new_range_token(int type, char **rng);
t_str_token		*glob_new_str_token(int type, char **str);
t_chr_token		*glob_new_chr_token(int type, char **str);
char			*match_word(t_globtok *tok, char *param, int greedy);
int				tokenize_word_pattern(t_submatch *gl);
void			walk_const(char **s);

#endif
