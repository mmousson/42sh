/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_edition.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:10:59 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 10:59:55 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VI_EDITION_H
# define _VI_EDITION_H

# define MODE 3

typedef enum				e_emode
{
	MNORMAL,
	MVI
}							t_emode;

typedef struct				s_undo
{
	char					*command;
	int						pos;
	struct s_undo			*next;
}							t_undo;

typedef struct				s_mode
{
	char					n_select;
	char					v_command;
	char					v_insert;
	char					v_visual;
	char					v_yank;
	char					v_del;
	char					v_replace_one;
	char					v_prior[4];
	char					v_lastc;
	char					v_lasta;
	int						v_pos;
	char					v_replace;
	char					mode[MODE];
	char					saved;
	t_undo					*undo;
}							t_mode;

int							line_vi(char *str, int ret);

/*
**	dispatcher
*/

int							vi_command(char *str, int ret);
int							vi_motion(char *str, int ret);
int							vi_delete(char *str, int ret);
int							vi_yank(char *str, int ret);
int							vi_visual(char *str, int ret);
int							vi_history(char *str, int ret);
int							vi_insert(char *str, int ret);
int							vi_paste(char *str, int ret);
int							vi_undo(char *str, int ret);

/*
**	jump_motion
*/

void						vi_ejump(int count, char c);
void						vi_pipejump(int count);
void						vi_jump_occur(char c, int i, int count);

/*
**	allocation/free
*/

void						vi_init_undo(void);
void						vi_add_undo(void);
int							vi_delundo(void);
void						vi_free_undo(t_undo *undo);
int							vi_hash_insert(void);
char						*vi_replace_str(char *str, int len);
void						vi_alloc_count(void);
int							vi_del_count(void);

/*
**	utility
*/

int							vi_get_count(char *str);
void						vi_reset_count(char *str);
int							vi_reset_mode(int ins, int com, int replace);
int							vi_get_prior_flag(char *str, int ret);
void						vi_repeat(void);
void						vi_rev_repeat(void);
void						vi_cdel(void);
void						vi_cpy(void);
void						vi_undo_update_pos(void);
int							vi_new_mode(t_emode mode);
void						vi_reset_cursor(t_undo *tmp, int u);

#endif
