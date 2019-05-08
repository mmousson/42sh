/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:49:53 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/07 10:47:12 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _AUTO_COMPLETION_H
# define _AUTO_COMPLETION_H

typedef struct			s_lstword
{
	char				*name;
	int					type;
	struct s_lstword	*next;
}						t_lstword;

int						auto_completion(char *str, int ret);
int						auto_isblank(void);
int						auto_getype(void);
int						auto_ispathcarac(char c);
int						auto_newtoken(char c);

/*
**	alloc
*/

char					*auto_getpath(void);
char					*auto_getroot(void);
void					auto_lstword(t_lstword *lstword, char *name, int type);
t_lstword				*auto_new_lstword(void);
void					auto_free_lstword(t_lstword *lstword);

/*
**	print
*/

int						auto_printword(char *path, char *root);
#endif
