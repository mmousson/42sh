/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:08:58 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/26 15:01:10 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H
# define NB_PR 7
# define NB_TY 4
# define NB_CH 15
# define DBL 20

/*
** enum e_charac, used relating to the lexing matrix, 1st
** ZER - 0 : \0
** CHA - 1 : is a char if not specified in another caharac
** SPA - 2 : SPAce, ' '
** REL - 3 : REdirection Left, '<'
** RER - 4 : REdirection Right, '>'
** DQT - 5 : Double QuoTe, '"'
** SDQ - 6 : Simple QuoTe, '''
** PAO - 7 : Parenthesis Open, '('
** ESP - 8 : ESPerluette, '&'
** BSL - 9: Back SLash, '\'
** PIP - 10 : PIPe, '|'
** SMC - 11: SeMiColomn, ';'
** PAC - 12: Parenthesis Closure, ')'
** EXC - 13: EXClamation point, '!'
** DOL - 14: DOLlard, '$'
** EXP - 15: to_expend
*/

typedef enum		e_charac
{
	ZER = 0,
	CHA,
	SPA,
	REL,
	RER,
	DQT,
	SQT,
	PAO,
	ESP,
	BSL,
	PIP,
	SMC,
	PAC,
	EXC,
	DOL,
	EXP
}					t_charac;

typedef enum		e_prepa
{
	CHAR = 0,
	SMCL,
	REDI,
	PIPE,
	SPAC,
	ENDT,
	SEPA,
	EROR,
	MORE
}					t_prepa;

typedef struct		s_tok
{
	struct s_tok	*next;
	char			*content;
	int				status;
}					t_tok;

typedef struct		s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	int				type;
	char			*content;
}					t_tree;

typedef struct		s_sep
{
	int				start;
	int				end;
}					t_sep;

void				ft_print_token(t_tok *tok);
t_tree				*ft_init_tree(void);
int					lex_get_ch(char c);

/*
** Function pre parsing
*/

int					is_sepa_tok(t_tok *token);
int					is_sep(int status);
int					pars_prepars(t_tok *token);
void				expand_arith(t_tok **token);

/*
** Function parsing
*/

int					tok_is_stat(t_tok *token, int status);
t_tree				*ft_pars_line(t_tok *tok, int start, int end);
t_tree				*ft_pars_cmd(t_tok *tok, int start, int end);
t_tree				*ft_pars_word(t_tok *tok, int start, int end);
t_tree				*ft_pars_nword(t_tok *tok, int start, int end);
t_tree				*ft_pars_pipe(t_tok *tok, int start, int end);
t_tree				*ft_pars_part(t_tok *tok, int start, int end);
t_tree				*ft_pars_red(t_tok *tok, int start, int end);

/*
** Function parsing son
*/

t_tree				*ft_sep(t_tok *tok, int start, int end, char c);
t_tree				*ft_word_sp(t_tok *tok, int start, int end);
t_tree				*ft_pars_rer_rig(t_tok *token, int start, int end);
t_tree				*ft_pars_rer_lef(t_tok *token, int start, int end);

/*
** Expend Function
*/

t_tree				*ft_expend(t_tree *tree, char **arge);
char				*ft_cmpct(t_tree *tree, char **arge);
int					is_clean(int val);
char				*ft_doll(t_tree *tree, char **arge);

/*
** Tool Function
*/

void				lex_free_token(t_tok *token);
t_tok				*ft_go_start(t_tok *token, int start);
t_tree				*ft_select_pars(t_tok *tok, int st, int end, char c);
void				ft_cleans_spa(int *start, int *end, t_tok *token);
t_tok				*ft_go_status(t_tok *token, int *pos, int status, int end);

/*
** tree Function
*/

t_tree				*ft_end_branch(void);
void				*ft_free_tree(t_tree *tree);

/*
** Print Function
*/

void				ft_print_tree(t_tree *tree);
void				ft_print_ch_hash(int ch);
#endif
