/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 21:36:53 by tduval            #+#    #+#             */
/*   Updated: 2019/05/29 12:12:51 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

int		build_pwd_tab(char ***arg_tab, char ***pwd_tab, int pwd_tab_len);
int		cd_options_parser(char **args, int *options, int *pos_args);
char	*get_final_path(char **path, char **cdenv);
char	*get_pwd_for_cd(int pos_args, char **args, char **cdenv);
int		change_directory(char ***env, char *pwd, char **cdenv, int options);
void	free_cd_tabs(char **tmp, char **nenv, char **narg);
int		blt_cd(int argc, char **argv, char ***env);
int		check_path_errors(char *path);
char	*ft_strjointab(char **arr, char sep);

#endif
