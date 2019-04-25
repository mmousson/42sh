/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:08:58 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/17 04:01:12 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H
# define NB_CH 17

/*
** enum e_charac, used relating to the lexing matrix, 1st
** ZER - 0 : \0
** CHA - 1 : is a char if not specified in another caharac
** INT - 2 : within ASCII '0' and '9'
** SPA - 3 : SPAce, ' '
** REL - 4 : REdirection Left, '<'
** RER - 5 : REdirection Right, '>'
** DQT - 6 : Double QuoTe, '"'
** SDQ - 7 : Simple QuoTe, '''
** ESP - 8 : ESPerluette, '&'
** BSL - 9 : Back SLash, '\'
** DOL - 10: DOLlar, '$'
** TIL - 11: TILde, '~'
** PIP - 12: PIPe, '|'
** SMC - 13: SeMiColomn, ';'
** DAS - 14: DASh, '-'
** SLA - 15: SLAsh, '/'
** NWL - 16: NeWLine, '\n'
*/

typedef enum		e_charac
{
	ZER = 0,
	CHA,
	INT,
	SPA,
	REL,
	RER,
	DQT,
	SQT,
	ESP,
	BSL,
	DOL,
	TIL,
	PIP,
	SMC,
	DAS,
	SLA,
	NWL
}					t_charac;


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

t_tok				*ft_init_token(void);
void				ft_print_token(t_tok *tok);
t_tree				*ft_init_tree(void);
int					ft_get_ch(char c);

/*
** Function parsing
*/

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
** Tool Function
*/

t_tok				*ft_go_start(t_tok *token, int start);
t_tree				*ft_select_pars(t_tok *tok, int st, int end, char c);
void				ft_cleans_spa(int *start, int *end, t_tok *token);
t_tok				*ft_go_status(t_tok *token, int *pos, int status, int end);

/*
** tree Function
*/

t_tree				*ft_end_branch(void);

/*
** Print Function
*/

void				ft_print_tree(t_tree *tree);
void				ft_print_ch_hash(int ch);
#endif
