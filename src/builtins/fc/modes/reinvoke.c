/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reinvoke.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:25:11 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/04 17:25:11 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"
#include "lex.h"

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

int	blt_fc_reinvoke(t_options_infos *inf, char ***env)
{
	int		ret;
	size_t	first_len;
	size_t	old_len;
	char	*catch;
	char	*fresh;

	if (inf->dash_s->old != NULL && inf->dash_s->new != NULL)
	{
		catch = ft_strstr(inf->from->line, inf->dash_s->old);
		fresh = ft_strsub(inf->from->line, 0, catch - inf->from->line);
		first_len = ft_strlen(fresh);
		old_len = ft_strlen(inf->dash_s->old);
		catch = ft_strjoin(fresh, inf->dash_s->new);
		ft_strdel(&fresh);
		fresh = catch;
		catch = ft_strjoin(fresh, inf->from->line + old_len + first_len);
		ft_strdel(&fresh);
		fresh = catch;
	}
	else
		fresh = inf->from->line;
	ret = !lex_str(&fresh, env);
	ft_strdel(&fresh);
	return (ret);
}
