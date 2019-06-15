/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 15:04:31 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 10:37:58 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# include "job_control_42.h"
# include "lex.h"

typedef struct		s_dup
{
	int				og;
	int				dir;
	int				int_og;
	int				int_dir;
	char			*name_og;
	char			*name_dir;
	int				simple;
	int				is_here;
}					t_dup;

typedef struct		s_lsther
{
	struct s_lsther	*next;
	char			*name;
}					t_lsther;

typedef struct		s_red
{
	t_lsther		*lsther;
	int				type;
	int				srt;
	int				end;
	int				close;
	char			*end_nm;
	struct s_red	*next;
}					t_red;

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
	int				dir_creat;
	t_lstred		*lstred;
	struct s_launch	*next;
}					t_launch;

t_red				*ft_init_red(void);
t_launch			*ft_init_cmd(char **argv);
char				**extend(char **argv, char *str);
void				ft_exec(t_tree *tree, char ***arge, int sep);
int					ft_path(char *name, char **path, char **arge);
int					ft_fct(char *name, char **path, char **arge);
int					is_exec(char *path);
char				**ft_split_path(char **env);
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
int					ft_launch_cmd(t_launch **cmd, char ***arge, int status);
void				ft_launch_last(t_launch *cmd, char ***arge);
int					ft_launch_red(t_red *red, t_launch *cmd, char ***arge);
void				ft_res_pile(t_launch *cmd);
void				ft_add_pile(int og, int dir, t_launch *cmd, int close);
int					ft_heredoc(char *end, char ***arge, t_red *red);
int					end_agg(char *str);
int					ft_heredoc_read(t_dup *dup, t_red *red);
void				add_name(t_red *red, char *str);
void				pile_red(t_dup *dup, t_launch *cmd, int close);
char				*ft_getenv(char **env, char *name);

void				exe_print_job(t_job *job);
t_job				*exe_load_job(t_launch *cmd, char ***arge);

#endif
