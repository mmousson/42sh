/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:21:08 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/11 19:37:22 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LINE_EDITION_H
# define _LINE_EDITION_H

# include <termios.h>
# include <termcap.h>

# define LJUMP "\033\033[D"
# define RJUMP "\033\033[C"
# define UJUMP "\033\033[A"
# define DJUMP "\033\033[B"
# define TEND "\033OF"
# define CTRLD '\004'

# define MODE 3

typedef enum			e_error
{
	TBADFD,
	TTTYNAME,
	TMALLOC,
	TIOCTL,
	TBADARG
}						t_error;

typedef enum			e_move
{
	MUP = 1,
	MDOWN,
	MLEFT,
	MRIGHT
}						t_move;

typedef enum			e_prompt
{
	PBASIC = 3,
	PQUOTE = 7,
	PDQUOTE = 8,
	PPIPE = 6,
	PHEREDOC = 9,
}						t_prompt;

typedef enum			e_emode
{
	MNORMAL,
	MVI,
	MREADLINE
}						t_emode;

typedef struct			s_tc
{
	int					tc;
	char				*key[5];
	char				*cm;
	char				*cl;
	char				*dl;
	char				*dc;
	char				*cr;
	char				*le;
	char				*nd;
	char				*sc;
	char				*rc;
	char				*up;
	char				*doo;
	char				*kh;
	char				*kd;
	char				*mr;
	char				*me;
	char				*cd;
}						t_tc;

typedef struct			s_cm
{
	int					pos;
	int					term_x;
	int					term_y;
	int					tmpy;
}						t_cm;

typedef struct			s_cpy
{
	char				*str;
	int					pos;
}						t_cpy;

typedef struct			s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct			s_mode
{
	int					mode[MODE];
	int					n_select;
	int					v_command;
	int					v_insert;
	int					v_count;
}						t_mode;

typedef struct			s_env
{
	struct termios		term;
	t_tc				*tc;
	t_cm				*cm;
	t_cpy				*cpy;
	int					t_fd;
	int					isatty;
	char				*line;
	char				*oldline;
	int					p_size;
	t_history			*ry;
	t_prompt			prompt;
	int					index;
	int					sigc;
	int					ctrld;
	t_mode				*mode;
	int					del;
	int					len;
}						t_env;

/*
** term_config
*/

void					ft_configterm(t_env *env);
void					ft_errorterm(t_error error, t_env *env);
void					ft_term_manager(t_env *env);
int						ft_quiterm(t_env *env);
void					ft_delenv(t_env *env);
void					ft_switch_term(t_env *env, int reset);
void					ft_update_termsize(t_env *env);

/*
**	line_read
*/

int						ft_reader(t_env *env, char *argv);
int						ft_update_line(t_env *env, char *str, int ret);
char					*ft_get_line(t_env *env, t_prompt prompt, char *argv);
int						ft_line_manager(t_env *env, char *str, int ret);
int						ft_line_arrow(t_env *env, char *str);
int						ft_line_ascii(t_env *env, char *str, int ret);
int						ft_line_history(t_env *env, char *str);
int						ft_read_isnotatty(t_env *env);
int						ft_read_isarg(t_env *env, char *argv);

/*
** termcaps
*/

int						ft_addtermcaps(t_tc *tc);
void					ft_active_termcaps(t_env *env);
int						ft_check_termcaps(t_tc tc);

/*
** cursor_motion
*/

void					ft_cursor_motion(t_env *env, t_move move, int len);
void					ft_cursor_ry(t_env *env);
void					ft_ljump(t_env *env);
void					ft_rjump(t_env *env);
void					ft_home(t_env *env);
void					ft_end(t_env *env);
void					ft_clear_line(t_env *env);
int						ft_getx(t_env *env, int pos);
int						ft_gety(t_env *env, int pos);
int						ft_get_termroom(t_env *env);
void					ft_reset_cursor(t_env *env);
int						ft_get_origin_pos(t_env *env);

/*
**	line_alloc
*/

char					*ft_addstr(t_env *env, char *str);
char					*ft_delchar(t_env *env, int size);
char					*ft_delchar_bs(t_env *env , int size);
char					*ft_alloc_history(t_env *env, int stline);
char					*ft_get_prompt(t_prompt prompt);

/*
**	history
*/

void					ft_get_uhistory(t_env *env);
void					ft_get_dhistory(t_env *env);
void					ft_reset_history(t_env *env);

/*
**	signal
*/

void					ft_signal_handler(int val);
void					ft_signal(int sg);
t_env					*signal_saved(t_env *env);
void					ft_sigint(void);
void					ft_sigwinch(void);
void					ft_reset_signal(int val);
void					ft_null(int sg);
void					ft_setsig_child(int val);

/*
**	cpy/past
*/

void					ft_paste(t_env *env, char *str);
void					ft_init_cpy(t_env *env);
int						ft_line_cpy(t_env *env, char *str, int ret);

/*
**	key
*/

int						ft_isaltc(char *str);
int						ft_isaltx(char *str);
int						ft_isaltv(char *str);

/*
**	print
*/

void					ft_print_line(t_env *env);

/*
**	mode
*/


int						ft_vi(t_env *env, char *str);
int						ft_read_line(t_env *env, char *str);
int						ft_tmp(t_env *env, char *str);

/*
**	vi_mode
*/

int						ft_line_vi(t_env *env, char *str, int ret);
int						ft_vi_command(t_env *env, char *str, int ret);
int						ft_hash_insert(t_env *env);
void						ft_get_count(t_env *env, char *str);
void						ft_reset_count(t_env *env, char *str);
int						ft_reset_mode(t_env *env);

/*
**	read_line_mode
*/

int						ft_line_readline(t_env *env, char *str, int ret);
#endif
