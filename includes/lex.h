/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:14:37 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/04 15:53:57 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "line_edition.h"
# include "pars.h"

# define BUF 1024
# define NB_STATE 13

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
** DS - 13: Double Silent quote, double quote witch are note store in buff
** SS - 14: Simple Silent quote, simple quote witche are not store in buff
** EN - 15: ENd, end of the lexing phasis
** VA - 16: VAlidation, Storing current buff whith char state
** VS - 17: Validation Star, Validation, but manage current char the next turn
** MO - 18: MOre, incomplete lexing, ask for more char
** SV - 19: Silent Validator, does not store last char
*/

typedef enum		e_state
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
	DS,
	SS,
	EN,
	VA,
	VS,
	MO,
	SV
}					t_state;

typedef struct		s_stat
{
	int				status;
	int				old_status;
	int				ch;
	char			cha;
	int				k;
	char			*load;
}					t_stat;

int					ft_echo(char **args, char ***env);
int					ft_cd(char **args, char ***env);
int					ft_env(char **args, char ***env);
int					ft_setenv(char **args, char ***env);
int					ft_unsetenv(char **args, char ***env);
char				**ft_tabdup(char **tabl);
int					ft_lex(char **str, char ***arge);
int					ft_get_next_state(int state, int ch);
t_stat				*ft_init_stat(void);
int					proc(t_stat *stat, char buff[BUF], t_tok *tok);
void				ft_add_token(char buf[BUF], char *ld, int stat, t_tok *tok);
void				ft_add_char(char buff[BUF], char **load, char cha);
void				ft_free_stat(t_stat *stat);
int					ft_more(t_stat *stat, char **str, int nl);
int					ft_pars(t_tok *tok, char ***arge, char *str);

/*
** fonctions affichages
*/

void				ft_print_stat_fd(int stat, int fd);
void				ft_print_ch_fd(int ch, int fd);
#endif
