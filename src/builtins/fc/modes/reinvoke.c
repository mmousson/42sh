/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reinvoke.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:25:11 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/10 16:55:25 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"
#include "lex.h"

/*
**	Because of the NORM --"
*/

static char	*malloc_error(char *to_del)
{
	if (to_del != NULL)
		ft_strdel(&to_del);
	ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
	return (NULL);
}

/*
**	This function generates the actual new command to be re-invoked, taking
**	the 'old=new' operand into account, if any
**
**	Arguments:
**	inf -> A pointer to the Data-Structure holding all informations about
**		the current 'fc' utility instance
**
**	Return Value:
**	NULL -> An Internal Malloc Error Occured
**	NON-NULL -> The fresh new command
*/

static char	*get_fresh_command(t_options_infos *inf)
{
	size_t	first_len;
	size_t	old_len;
	char	*catch;
	char	*fresh;

	catch = ft_strstr(inf->from->line, inf->dash_s->old);
	if (!(fresh = ft_strsub(inf->from->line, 0, catch - inf->from->line)))
		return (malloc_error(NULL));
	first_len = ft_strlen(fresh);
	old_len = ft_strlen(inf->dash_s->old);
	if ((catch = ft_strjoin(fresh, inf->dash_s->new)) == NULL)
		return (malloc_error(fresh));
	ft_strdel(&fresh);
	fresh = catch;
	if (!(catch = ft_strjoin(fresh, inf->from->line + old_len + first_len)))
		return (malloc_error(fresh));
	ft_strdel(&fresh);
	fresh = catch;
	return (fresh);
}

/*
**	This function directly reinvokes a command from the history without
**	editing it
**	If an operand of the form 'old=new' has been provided to the utility,
**	then the string 'old' from the command being re-executed is replaced
**	with 'new'
**
**	Arguments:
**	inf -> A pointer to the Data-Structure holding all informations about
**		the current 'fc' utility instance
**	env -> The shell's current environment full-access pointer
**
**	Return Value:
**	(-1) -> An internal Malloc Error occured
**	Otherwise always the return value of 'lex_str' function, launching
**		the re-invoked command
*/

int			blt_fc_reinvoke(t_options_infos *inf, char ***env)
{
	int		ret;
	char	*fresh;

	if (inf->dash_s->old != NULL && inf->dash_s->new != NULL)
		fresh = get_fresh_command(inf);
	else
	{
		if ((fresh = ft_strdup(inf->from->line)) == NULL)
		{
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
			return (2);
		}
	}
	ret = !lex_str(&fresh, env);
	ft_strdel(&fresh);
	return (ret);
}
