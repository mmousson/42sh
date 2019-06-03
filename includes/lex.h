/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:14:37 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/31 17:06:27 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "line_edition.h"
# include "pars.h"

# define BUF 1024
# define NB_STATE 11

/*
** enum e_state, used relating to the lexing matrix, 2nd
** ST - 0 :	STart
** CH - 1 :	CHar, classical String mode
** SP - 2 :	SPace, ' '
** RL - 3 :	Redirection Left, '<'
** RR - 4 :	Redirection Right, '>'
** DQ - 5 :	Double Quote, '"'
** SQ - 6 :	Simple Quote, '''
** PS - 7 :	Parenthesis Simple, '('
** ES - 8 :	Esperluette, '&'
** BS - 9:	Back Slash, '\'
** PI - 10: PIpe, '|'
** ----------------------------------------- end of matrix
** SK - 11:	Store in StacK, used for stacking " ' $( and (
** US - 12:	Un Stack, used for Un Stack previously stacked elmt
**			Could result in a lexing error if not well stacked/unstacked
** ML - 13:	Mini_lexer, for !expand
** DB - 14:	Double quote, backslash, escape authorized elmt
** DO - 15: Dollard store
** VA - 16:	VAlidation, Storing current buff whith char state
** VS - 17:	Validation Star, Validation, but manage current char the next turn
** MO - 18:	MOre, incomplete lexing, ask for more char
** SD - 19: Store Dollard
** VO - 20: Validate Old
** ER - -1: Error
** EN - -2:	ENd, end of the lexing phasis
** EP - -3: Error Patrenthesis, for stacking error
** ED - -4: Error Dollard
*/

typedef enum	e_state
{
	ST = 0,
	CH,
	SP,
	RL,
	RR,
	DQ,
	SQ,
	PS,
	ES,
	BS,
	PI,
	SK,
	US,
	ML,
	DB,
	DO,
	VA,
	VS,
	MO,
	SD,
	VO,
	ER = -1,
	EN = -2,
	EP = -3,
	EC = -4,
	ED = -5
}				t_state;

typedef struct	s_st
{
	int			elmt;
	struct s_st	*next;
}				t_st;

typedef struct	s_stat
{
	int			status;
	int			old_status;
	int			older_status;
	int			ch;
	char		cha;
	int			k;
	char		*load;
	t_st		*stack;
}				t_stat;

char			**ft_tabdup(char **tabl);

t_st			*init_pile(int status);
void			lex_add_tok(char buf[BUF], char *ld, int stat, t_tok *tok);
void			lex_add_char(char buff[BUF], char **load, char cha);
void			lex_free_stat(t_stat *stat);
t_tok			*lex_init_token(void);
t_tok			*new_token_char(char *str);
t_tok			*new_token_space(void);
t_stat			*lex_init_stat(void);
int				lex_proc(t_stat *stat, char buff[BUF], t_tok **tok, char **str);
int				lex_str(char **str, char ***arge);
int				lex_more(t_stat *stat, char **str, int nl);
int				lex_get_next_state(int state, int ch);
int				pars_tok(t_tok *tok, char ***arge, char *str);
int				lex_exclam(t_stat *stat, t_tok **tok, char **str);
int				lex_back_slash_quote(t_stat *stat, char **str, char buff[BUF]);
int				lex_store(t_stat *stat, char buff[BUF]);
int				lex_last_pile(t_stat *stat);
int				lex_store_dol(t_stat *stat, char buff[BUF], char **str);
int				lex_pile_up(t_stat *stat, char buff[BUF]);
int				lex_step(t_stat **stat, char **str);
int				lex_welding(t_stat *stat);
int				error_ep_or_ec(char close, t_stat *stat);

/*
** fonctions affichages
*/

void			ft_print_stat_fd(int stat, int fd);
void			ft_print_ch_fd(int ch, int fd);
void			lex_print_stack(t_st *stack);
#endif
