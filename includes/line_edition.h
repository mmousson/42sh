/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:21:08 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 10:54:10 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LINE_EDITION_H
# define _LINE_EDITION_H

# include <termios.h>
# include <termcap.h>
#include "libft.h"

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
	PBACKS = 4,
	PDEF = 2
}						t_prompt;

typedef enum			e_emode
{
	MNORMAL,
	MVI,
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

typedef struct			s_undo
{
	char				*command;
	struct s_undo		*next;
}						t_undo;

typedef struct			s_mode
{
	int					n_select;
	int					v_command;
	int					v_insert;
	int					v_visual;
	int					v_yank;
	int					v_del;
	int					v_count;
	int					v_prior[4];
	char				v_lastc;
	char				v_lasta;
	int					v_replace;
	int					v_pos;
	int					mode[MODE];
	char				s_buffer[BUFF_SIZE];
	int					saved;
	t_undo				*undo;
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

struct s_env			g_env;

/*
** term_config
*/

void					ft_configterm(void);
void					ft_errorterm(t_error error);
void					ft_term_manager(void);
int						ft_quiterm(void);
void					ft_delenv(void);
void					ft_switch_term(int reset);
void					ft_update_termsize(void);

/*
**	line_read
*/

int						ft_reader(char *argv);
int						ft_update_line(char *str, int ret);
char					*ft_get_line(t_prompt prompt, char *argv);
int						ft_line_manager(char *str, int ret);
int						ft_line_arrow(char *str);
int						ft_line_ascii(char *str, int ret);
int						ft_line_history(char *str);
int						ft_read_isnotatty(void);
int						ft_read_isarg(char *argv);

/*
** termcaps
*/

int						ft_addtermcaps(t_tc *tc);
void					ft_active_termcaps(void);
int						ft_check_termcaps(t_tc tc);

/*
** cursor_motion
*/

void					ft_cursor_motion(t_move move, int len);
void					ft_cursor_ry(void);
void					ft_ljump(void);
void					ft_rjump(void);
void					ft_home(int blank);
void					ft_end(void);
void					ft_clear_line(void);
int						ft_getx(int pos);
int						ft_gety(int pos);
int						ft_get_termroom(void);
void					ft_reset_cursor(void);
int						ft_get_origin_pos(void);

/*
**	line_alloc
*/

char					*ft_addstr(char *str);
char					*ft_delchar(int size);
char					*ft_delchar_bs(int size);
char					*ft_alloc_history(int stline);
char					*ft_get_prompt(t_prompt prompt);

/*
**	history
*/

void					ft_get_uhistory(int count);
void					ft_get_dhistory(int count);
void					ft_reset_history(void);

/*
**	signal
*/

void					ft_signal_handler(int val);
void					ft_signal(int sg);
void					ft_sigint(void);
void					ft_sigwinch(void);
void					ft_reset_signal(int val);
void					ft_null(int sg);
void					ft_setsig_child(int val);

/*
**	cpy/past
*/

void					ft_paste(char *str, int count);
void					ft_init_cpy(void);
int						ft_line_cpy(char *str, int ret);

/*
**	key
*/

int						ft_isaltc(char *str);
int						ft_isaltx(char *str);
int						ft_isaltv(char *str);

/*
**	print
*/

void					ft_print_line(void);

/*
**	mode
*/


int						ft_vi(char *str);
int						ft_read_line(char *str);
int						ft_tmp(char *str);

/*
**	vi_mode
*/

int						ft_line_vi(char *str, int ret);
int						ft_vi_command(char *str, int ret);
int						ft_vi_motion(char *str, int ret);
int						ft_vi_delete(char *str, int ret);
int						ft_vi_yank(char *str, int ret);
int						ft_vi_visual(char *str, int ret);
int						ft_vi_history(char *str, int ret);
int						ft_vi_insert(char *str, int ret);
int						ft_vi_paste(char *str, int ret);
int						ft_vi_undo(char *str, int ret);
int						ft_hash_insert(void);
int						ft_get_count(char *str);
void					ft_reset_count(char *str);
int						ft_reset_mode(int ins, int com);
void					ft_wjump(int count);
void					ft_ejump(int count);
void					ft_bjump(int count);
void					ft_pipejump(int count);
void					ft_jump_occur(char c, int i, int count);
int						ft_get_prior_flag(char *str);
void					ft_repeat(void);
void					ft_rev_repeat(void);
char					*ft_replace_str(char *str, int len);
void					ft_cdel(void);
void					ft_vi_cpy(void);
void					ft_init_undo(void);
void					ft_add_undo(void);
int						ft_delundo(t_undo *undo);
#endif
