/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:03:45 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/27 17:41:53 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "pars.h"
# include "lex.h"

int		expand_manager(char **str, char ***arge, t_tok *token, int red);
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
int		expand_filename(char **path, t_tok *token, int ret);
int		expand_tilde(char **str);
int		expand_tild_unit(char **str, int *k);
char	*take_word_expand(const char *str, char ***arge);
int		expand_question(char *var, const char *str, char ***arge);
void	expand_glo(char **value, const char *str, char *var, char ***arge);
char	*remove_substring(char *param, char *word, int suffix, int greedy);
void	expand_size_word(char **value, const char *str, char ***arge);
int		expand_alias(char **str, char *word, t_stat *stat);
int		is_reserved(char *str);
char	*grep_first(char *word);
char	*grep_next_word(char *str, t_stat *stat);
char	*grep_iter(char *word, int iter, int *start);
char	*get_alias(char *value);
int		expand_cmd_sub(char **path, char ***arge, t_tok *token);
int		job_command_substitution(char **command, char ***env);

#endif
