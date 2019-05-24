/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:03:45 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/24 22:11:43 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

int		expand_manager(char ***argv, char ***arge);
int		expand_quote_removal(char ***argv);
int		expand_shell_param(char ***argv, char ***arge);
char	*expand_param(const char *str, char ***arge, int *end);
int		insert_word(char **str, char *expand, int start, int len);
#endif
