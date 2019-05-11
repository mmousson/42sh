/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:21:08 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/11 18:41:10 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LINE_EDITION_H
# define _LINE_EDITION_H

# include <termios.h>
# include <termcap.h>
# include "libft.h"
# include "vi_edition.h"
# include "auto_completion.h"

# define UJUMP "\033\033[A"
# define DJUMP "\033\033[B"
# define TEND "\033OF"
# define CTRLA '\001'
# define CTRLB '\002'
# define CTRLD '\004'
# define CTRLE '\005'
# define CTRLF '\006'
# define CTRLK '\013'
# define CTRLN '\016'
# define CTRLP '\020'
# define CTRLT '\024'
# define CTRLU '\025'
# define CTRLW '\027'
# define CTRLX '\030'
# define CTRLY '\031'
# define CTRLUND '\037'

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
	char				*af;
}						t_tc;

typedef struct			s_cm
{
	int					pos;
	int					term_x;
	int					term_y;
	int					tmpy;
}						t_cm;

typedef struct			s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct			s_ctrlxx
{
	int					pmax;
	int					pmin;
	int					count_x;
	int					lastp;
}						t_ctrlxx;

typedef struct			s_env
{
	struct termios		term;
	t_tc				*tc;
	t_cm				*cm;
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
	int					cpos;
	char				s_buffer[BUFF_SIZE + 1];
	char				s_buffkill[BUFF_SIZE + 1];
	int					k_index;
	t_ctrlxx			*cx;
	int					count;
}						t_env;

struct s_env			g_env;

char					*line_get_readline(t_prompt prompt, char *argv);
int						line_manager(char *str, int ret);
int						line_update(char *str, int ret);
void					line_update_termsize(void);
int						line_return(void);
int						line_escap(void);

/*
** term_config
*/

void					sh_configterm(void);
void					sh_errorterm(t_error error);
void					sh_term_manager(void);
int						sh_quiterm(void);
void					sh_switch_term(int reset);

/*
**	dispatcher
*/

int						line_motion(char *str, int ret);
int						line_ascii(char *str, int ret);
int						line_history(char *str, int ret);
int						line_del(char *str, int ret);
int						line_undo(char *str, int ret);
int						line_inverse(char *str, int ret);

/*
**	read
*/

int						line_reader(char *argv);
int						line_read_isnotatty(void);
int						line_read_isarg(char *argv);

/*
** termcaps
*/

int						caps_addtermcaps(t_tc *tc);
void					caps_active_termcaps(void);
int						caps_check_termcaps(t_tc tc);

/*
** cursor_motion
*/

void					line_cursor_motion(t_move move, int len);
void					line_cursor_ry(void);
void					line_ljump(void);
void					line_rjump(void);
void					line_home(int blank);
int						line_end(void);
void					line_clear(void);
int						line_getx(int pos);
int						line_gety(int pos);
int						line_get_termroom(void);
void					line_reset_cursor(int ret_p);
int						line_get_origin_pos(void);
void					line_cxjump(void);

/*
**	line_alloc
*/

char					*line_addstr(char *str);
char					*line_delchar(int size);
char					*line_delchar_bs(int size);
char					*line_alloc_history(int stline);
char					*line_get_prompt(t_prompt prompt);
void					line_delenv(void);

/*
**	history
*/

void					line_get_uhistory(int count);
void					line_get_dhistory(int count);
void					line_reset_history(void);

/*
**	signal
*/

void					sig_handler(int val);
void					sig_manager(int sg);
void					sig_sigint(void);
void					sig_sigwinch(void);
void					sig_reset(int val);
void					sig_setchild(int val);

/*
**	cpy/past
*/

void					line_paste(char *str, int count);
void					line_init_cpy(void);
int						line_cpy(char *str, int ret);
void					line_escap_cpy(int move_cursor);

/*
**	key
*/

int						line_isaltc(char *str, int ret);
int						line_isaltx(char *str, int ret);
int						line_isaltv(char *str, int ret);
int						line_isaltf(char *str, int ret);
int						line_isaltb(char *str, int ret);
int						line_isaltt(char *str, int ret);
int						line_ctrld(void);

/*
**	print
*/

int						line_print(void);

/*
**	vi_readline
*/

int						line_isleft(char *str, int ret);
int						line_isright(char *str, int ret);
int						line_ishome(char *str, int ret);
int						line_isend(char *str, int ret);
int						line_iscx(char *str, int ret);
int						line_isdel(char *str, int ret);
int						line_isdelrword(char *str, int ret);

#endif
