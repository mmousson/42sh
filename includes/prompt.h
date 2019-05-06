/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:46:27 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/06 19:54:24 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# define BANNER_ARROW "\xee\x82\xB0 "
# define USER_FONT "\033[33m"
# define BANNER_START " \033[7;38;2;50;50;50m"
# define GIT_NO_GIT "\033[38;2;50;50;50;49m\xEE\x82\xB0\033[0m "
# define GIT_BRANCH_START "\033[0;38;2;50;50;50;48;2;"
# define GIT_UP_TO_DATE "50;200;50m"
# define GIT_NOT_UP_TO_DATE "209;8;28m"
# define GIT_RED_INFOS "209;8;28;38;2;255;255;255m"
# define GIT_END_BANNER " \033[38;2;0;200;0;49m\xEE\x82\xB0""\033[37m"
# define GIT_ERR_END_BANNER " \033[0;38;2;209;8;28m\xEE\x82\xB0""\033[37m"
# define WHITE_BOLD "\033[1;38;2;230;230;230m"

int		put_arrow(char *arrow);
int		prompt_format_path(char *path);
int		prompt_git_branch(char **env);
void	get_additions_deletions(int *plus, int *minus, char **env);

#endif
