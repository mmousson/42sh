/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexpars.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:13:45 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/07 18:06:26 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXPARS_H
# define LEXPARS_H

# define NB_STATE 14
# define NB_CARAC 12

# include "line_edition.h"

typedef enum		e_fnct
{
	ERROR = -1,
	NEWCHAR = 1,
	ADDCHAR = 2,
	ADDARG = 3,
	ADDCMD = 4,
	DOPIPE = 5,
	REDIN_N = 6,
	REDOUT_N = 7,
	LIMOUT = 8,
	QUIT = 9,
	REDIN = 10,
	REDOUT = 11,
	NEWINT = 12,
	ADDINT = 13,
	REDIN_CK = 14,
	REDOUT_CK = 15,
	REDIN_DB = 16,
	REDOUT_DN = 17,
	STQT_DB = 18,
	STQT_SP = 19,
	MOREQT = 20,
	ENDQT = 21
}					t_fnct;

typedef enum		e_charac
{
	CHAR = 0,
	INT,
	SPACE,
	CMDEND,
	PIPE,
	END,
	INF,
	SUP,
	QT_DB,
	QT_SP,
	EPERL,
	SEG
}					t_charac;

typedef enum		e_state
{
	S_START = 0,
	S_CHAR,
	S_INT,
	S_INF,
	S_SUP,
	S_INFDB,
	S_SUPDB,
	S_QTDB,
	S_QTSP,
	S_START_SP
}					t_state;

typedef struct		s_word
{
	struct s_word	*next;
	char			*value;
	int				news;
	int				type;
}					t_word;

typedef struct		s_cmd
{
	struct s_cmd	*next;
	struct s_word	*word;
	struct s_word	*redir;
	int				status;
	int				pipe;
}					t_cmd;

typedef struct		s_args
{
	char			***arge;
	int				k;
	int				agg;
	char			*str;
	t_cmd			*cmd;
	int				status;
	int				charac;
	int				old_status;
	t_env			*line;
	int				in;
	int				out;
	int				err;
}					t_args;

t_word				*ft_target(t_cmd *cmd);

int					nothing(t_args *args);
int					ft_newarg(t_args *args);
int					ft_starg(t_args *args);
int					ft_empargs(t_args *args);
int					ft_newcmd(t_args *args);
int					ft_pipe(t_args *args);
int					ft_eperl(t_args *args);
int					ft_lim(t_args *args);
int					ft_quit(t_args *args);
int					ft_redirect(t_args *args);
int					ft_newred(t_args *args);
int					ft_dbqt(t_args *args);
int					ft_spqt(t_args *args);
int					ft_more_pipe(t_args *args);

char				**ft_tab_dup(char **tabl);
int					ft_tab_size(char **env);

void				ft_pipe_close(int *fdpipe, int nbr_pipes);
void				ft_add_pile(int og, t_args *arg);
void				ft_res_red(t_args *arg);
void				ft_ctrld(t_args *args);
void				ft_free_words_tables(char **tabl);
void				ft_exit_clean_args(t_args *args, int ret);
int					ft_is_fct(char *name, char **arge);
int					error_open(char *str);
int					ft_heredoc(t_args *args, char *end);
int					ft_exec(t_cmd *cmd, char ***arge, t_args *args);
int					ft_fct(t_word *word, char **path, char **arge);
int					ft_manage_pipe(t_cmd *cmd, char ***arge, t_args *args);
int					ft_launch_red(t_word *red, t_args *args);
char				**ft_make_tabl(t_word *word);
int					do_fork(char *name, char **arg, char **env, t_args *args);
int					is_exec(char *path);
int					ft_path(char *name, char **path, char **arge);
char				**ft_split_path(char **env);
int					ft_pars(t_cmd *cmd, char ***arge, t_args *args, int ret);
void				ft_free_word(t_word *word);
void				ft_free_arg(t_args *arg);
int					ft_lex(char **str, t_env *env, char ***arge);
int					ft_charac(char k);
int					get_fct(int state, int charac);
int					get_status(int state, int charac);
int					ft_add_word(t_cmd *cmd, char k);
t_args				init_args(char *str, t_env *line, char ***arge);
t_word				*init_word(void);
t_cmd				*init_cmd(void);
void				ft_print_words(t_word *word);
void				ft_print_cmd(t_cmd *cmd);

#endif
