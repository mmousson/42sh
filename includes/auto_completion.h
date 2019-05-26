/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:49:53 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/25 14:50:35 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _AUTO_COMPLETION_H
# define _AUTO_COMPLETION_H

# include <dirent.h>

# define COMWOPT 2


typedef struct			s_name
{
	char			*name;
	char			*desc;
}				t_name;

typedef struct			s_lstword
{
	t_name			*name;
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
	char				*com_option;
	char				*var;
	int					spos;
}						t_autodata;

struct s_autodata		g_data;

int						auto_completion(char *str, int ret);
int						auto_getype(void);
void						auto_keep_comp(char *str, int ret);
int						auto_getstatype(char *name, char *carac, int index);

/*
**	iscarac
*/

int						auto_ispathcarac(char c);
int						auto_isvar(char c, char prev);
int						auto_newtoken(char c, char prev);
int						auto_ischar(char c, char prev);
int						auto_isoption(char c, char prev);
int						auto_isblank(void);

/*
**	alloc
*/

t_lstword				*auto_new_lstword(void);
void					auto_lstmanager(struct dirent *dt, int i);
void					auto_lstword(char *orig, char **name, int index);
void					auto_free(void);
void					auto_free_lstword(t_lstword *lw);
void					auto_filldata(void);
char					*auto_getpath(void);
char					*auto_getroot(void);
char					*auto_getvar(void);
char					*auto_alloc_name(char **str);
void					auto_lstoption(char **name, char **desc);

/*
**	print
*/

int						auto_printword(void);
int						auto_printaligned(void);
void					auto_printvar(void);
void					auto_printoption();

/*
**	utils
*/


int						auto_checkroot(char *name, char *root);
void					auto_calclen(void);
void					auto_sort(void);
void					auto_swapstr(char **a, char **b);
void					auto_swapint(int *a, int *b);
void					auto_swapchar(char *a, char *b);
int						auto_lenrootwbs(void);
int						auto_istabshift(char *str, int ret);
int						auto_check_double(char *name);

/*
**	completion
*/

int						auto_comproot(int back);
int						auto_compath(int back);
int						auto_compoption(int back);

/*
**	choose
*/

int						auto_choose(int back);
int						auto_return(void);

/*
**	termcaps
*/

void					auto_print_select(void);
void					auto_print_color(void);

/*
**	option_text
*/

void					auto_ls(int index, char **name, char **desc, int *loop);
#endif
