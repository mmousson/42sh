/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 21:36:53 by tduval            #+#    #+#             */
/*   Updated: 2019/05/04 03:18:30 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# define OPT_L	1
# define OPT_P	2

void	free_files(char **files);
char	*cd_get_pwd(char *cur);
char	cd_get_opts(char **argv, char **dir);

#endif
