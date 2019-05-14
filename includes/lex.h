/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:14:37 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/14 17:44:08 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "line_edition.h"
# include "pars.h"

# define BUF 1024
# define NB_STATE 16

/*
** enum e_state, used relating to the lexing matrix, 2nd
** ST - 0 : STart
** CH - 1 : CHar, classical String mode
** IN - 2 : INt, String with only ASCII within '0' and '9'
** SP - 3 : SPace, ' '
** RL - 4 : Redirection Left, '<'
** RR - 5 : Redirection Right, '>'
** DQ - 6 : Double Quote, '"'
** SQ - 7 : Simple Quote, '''
** ES - 8 : Esperluette, '&'
** BS - 9 : Back Slash, '\'
** DO - 10: Dollar, '$'
** TI - 11: TIlde, '~'
** PI - 12: PIpe, '|'
** PS - 13: Parenthesis Simple, '$('
** PD - 14: Parenthesis Double, "$(("
** CP - 15: Parenthesis Close, "$(()"
** DS - 16: Double Silent quote, double quote witch are note store in buff
** SS - 17: Simple Silent quote, simple quote witche are not store in buff
** EN - 18: ENd, end of the lexing phasis
** VA - 19: VAlidation, Storing current buff whith char state
** VS - 20: Validation Star, Validation, but manage current char the next turn
** MO - 21: MOre, incomplete lexing, ask for more char
** SV - 22: Silent Validator, does not store last char
** EP - 23: Error Parenthesis
** ML - 24: Mini_lexer, for !expand
** DB - 26: Double quote, backslash
*/

typedef enum	e_state
{
	ST = 0,
	CH,
	IN,
	SP,
	RL,
	RR,
	DQ,
	SQ,
	ES,
	BS,
	DO,
	TI,
	PI,
	PS,
	PD,
	CP,
	DS,
	SS,
	EN,
	VA,
	VS,
	MO,
 	SV,
	EP,
	ML,
	DB
}				t_state;

typedef struct	s_stat
{
	int			status;
	int			old_status;
	int			ch;
	char		cha;
	int			k;
	char		*load;
}				t_stat;

char			**ft_tabdup(char **tabl);

void			lex_add_tok(char buf[BUF], char *ld, int stat, t_tok *tok);
void			lex_add_char(char buff[BUF], char **load, char cha);
void			lex_free_stat(t_stat *stat);
t_tok			*lex_init_token(void);
t_stat			*lex_init_stat(void);
int				lex_proc(t_stat *stat, char buff[BUF], t_tok **tok, char **str);
int				lex_str(char **str, char ***arge);
int				lex_more(t_stat *stat, char **str, int nl);
int				lex_get_next_state(int state, int ch);
int				pars_tok(t_tok *tok, char ***arge, char *str);
int				lex_exclam(t_stat *stat, t_tok **tok, char **str);
int				lex_back_slash_quote(t_stat *stat, char **str, char buff[BUF]);

/*
** fonctions affichages
*/

void			ft_print_stat_fd(int stat, int fd);
void			ft_print_ch_fd(int ch, int fd);
#endif
