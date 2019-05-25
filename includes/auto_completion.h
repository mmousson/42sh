/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:49:53 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/23 17:12:37 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _AUTO_COMPLETION_H
# define _AUTO_COMPLETION_H

typedef struct			s_lstword
{
	char				*name;
	int					type;
	char				carac;
	int					len;
	int					select;
	struct s_lstword	*next;
}						t_lstword;

typedef struct			s_autodata
{
	int					status;
	int					type;
	struct s_lstword	*lw;
	int					wordpline;
	int					lenmax;
	int					lenlst;
	int					x;
	int					y;
	char				**path;
	char				*root;
	int					spos;
}						t_autodata;

struct s_autodata		g_data;

int						auto_completion(char *str, int ret);
int						auto_getype(void);
int						auto_ispathcarac(char c);
int						auto_isvar(char c, char prev);
int						auto_newtoken(char c, char prev);
int						auto_getstatype(char *name, char *carac, int index);

/*
**	alloc
*/

void					auto_lstword(char *orignal, char **name, int index);
t_lstword				*auto_new_lstword(void);
void					auto_free(void);
void					auto_free_lstword(t_lstword *lw);
void					auto_filldata(void);
char					*auto_getpath(void);
char					*auto_getroot(void);
char					*auto_alloc_name(char **str);

/*
**	print
*/

int						auto_printword(void);
int						auto_printaligned(void);
void					auto_printvar(void);

/*
**	utils
*/


int						auto_isblank(void);
int						auto_checkroot(char *name, char *root);
void					auto_calclen(void);
void					auto_sort(void);
void					auto_swapstr(char **a, char **b);
void					auto_swapint(int *a, int *b);
void					auto_swapchar(char *a, char *b);
int						auto_lenrootwbs(void);

/*
**	choose
*/

int						auto_choose(void);
int						auto_return(void);

/*
**	termcaps
*/

void					auto_print_select(void);
void					auto_print_color(void);
#endif
