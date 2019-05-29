/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:03:45 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/28 18:44:42 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "pars.h"

int		expand_manager(char **str, char ***arge, t_tok *token);
int		expand_quote_removal(char **str);
int		expand_shell_param(char **str, char ***arge);
char	*expand_param(const char *str, char ***arge, int *end);
char	*expand_curly(const char *str, char ***arge, int *end, int *error);
int		insert_word(char **str, char *expand, int start, int len);
int		is_char_exp(char c);
char	*get_spec_param(const char *word);
int		is_doll_exp(char c);
int		expand_param_word(char **str, char ***arge);
int		expand_arithmetic(char **str, char ***env);
int		expand_filename(char **path, t_tok *token);
#endif
