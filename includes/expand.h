/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:03:45 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/27 19:11:25 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

int		expand_filename(char **path);
int		expand_manager(char ***argv, char ***arge);
int		expand_quote_removal(char ***argv);
int		expand_shell_param(char ***argv, char ***arge);
char	*expand_param(const char *str, char ***arge, int *end);
char	*expand_curly(const char *str, char ***arge, int *end, int *error);
int		insert_word(char **str, char *expand, int start, int len);
int		is_char_exp(char c);
#endif
