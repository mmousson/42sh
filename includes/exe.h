/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 10:08:18 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/08 22:42:50 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# include "job_control_42.h"
# include "line_edition.h"
# include "pars.h"
# include "lex.h"

typedef struct		s_red
{
	int				type;
	int				srt;
	int				end;
	char			*end_nm;
	struct s_red	*next;
}					t_red;

typedef struct		s_lstfd
{
	int				fd;
	struct s_lstfd	*next;
}					t_lstfd;

typedef struct		s_launch
{
	char			**argv;
	t_red			*red;
	int				*fdpipe;
	int				nbr_pipe;
	int				will_red;
	int				in;
	int				out;
	int				err;
	t_lstfd			*lstfd;
	struct s_launch	*next;
}					t_launch;

t_red				*ft_init_red(void);
t_launch			*ft_init_cmd(char **argv);
char				**extend(char **argv, char *str);
void				ft_exec(t_tree *tree, char ***arge);
int					ft_path(char *name, char **path, char **arge);
int					ft_get_home_cmd(char *name);
int					ft_fct(char *name, char **path, char **arge);
int					is_exec(char *path);
char				**ft_split_path(char **env);
int					do_fork(char *name, char **arg, char **arge);
void				ft_cmd_nf(char *str);
int					ft_add_red(t_tree *tree, t_launch *cmd);
t_red				*ft_target_last(t_launch *cmd);
void				ft_add_argv(char *str, t_launch *cmd);
int					error_open(char *str);
void				ft_next_pipe(t_launch *cmd);
void				ft_launch_pipe(t_launch *cmd, char ***arge);
int					ft_pipe_close(int *fdpipe, int nbr_pipe);
int					ft_end_of_pipes(int *fdpipes, int nbr_pipres);
void				ft_free_cmd(t_launch *cmd);
void				ft_free_lstfd(t_lstfd *lstfd);
void				ft_launch_exe(t_launch *cmd, char ***arge);
void				ft_launch_cmd(t_launch **cmd, char ***arge);
void				ft_launch_last(t_launch *cmd, char ***arge);
int					ft_launch_red(t_red *red, t_launch *cmd);
void				ft_res_pile(t_launch *cmd);
void				ft_add_pile(int og, int dir, t_launch *cmd);
int					ft_heredoc(char *end, t_launch *cmd);

char				*ft_getenv(char **env, char *name);
int					ft_do_home(int k, char **argv, char ***arge);

void				exe_print_job(t_job *job);
t_job				*exe_load_job(t_launch *cmd, char ***arge);

#endif
