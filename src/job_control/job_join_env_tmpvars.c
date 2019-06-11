/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_join_env_tmpvars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:40:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/11 17:40:47 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	This function counts the number of elements contained in the shell's TMP
**	variables
**
**	Arguments: NONE
**
**	Return Value (size_t): The number of counted elements - No Error Code
*/

static size_t	job_tmpvars_list_depth(void)
{
	size_t	res;
	t_vars	*current;

	res = 0;
	current = g_shell_tmp_vars;
	while (current)
	{
		current = current->next;
		res++;
	}
	return (res);
}

/*
**	This function counts the number of elements contained in the shell's
**	current environment definition
**
**	Arguments:
**	env (char **) -> The shell's current environment definition
**
**	Return Value (size_t): The number of counted elements - No Error Code
*/

static size_t	job_env_depth(char **env)
{
	size_t	res;

	res = 0;
	while (env[res] != NULL)
		res++;
	return (res);
}

/*
**	This function joins the field 'name' and 'value' of a 't_vars' structure
**	into a single string of the form "%s=%s", name, value
**
**	Arguments:
**	current (t_vars *) -> A pointer to the Data-Structure representing the
**		TMP variable to extrcar the string from
**
**	Return Value (char **):
**	NULL -> An malloc error occured
**	NON-NULL -> The newly allocated string representing the variable
*/

static char		*job_join_tmpvar_def(t_vars *current)
{
	char	*res;
	char	*tmp;

	if ((tmp = ft_strjoin(current->name, "=")) == NULL)
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (NULL);
	}
	if ((res = ft_strjoin(tmp, current->value)) == NULL)
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
	ft_strdel(&tmp);
	return (res);
}

/*
**	Once the 'res' array has been allocated, this function will take care
**	of filling it up with 'job_join_tmpvar_def' function for TMP variables
**	and 'ft_strdup' for variables from the shell's environment
**	The address of the filled up array if then returned
**
**	Arguments:
**	res (char **) -> The array which will hold all variables defintions
**	env (char **) -> The shell's current environment definition
**	s_env (size_t) -> The number of elements contained in the environment
**	s_tmp (size_t) -> The number of TMP variables contained in g_shell_tmp_vars
**
**	Return Value (char **): ALWAYS THE ADDRESS OF 'res' ARGUMENT
*/

static char		**job_fill_with_env_and_tmp(char **res, char **env,
	size_t s_env, size_t s_tmp)
{
	size_t	i;
	t_vars	*current;

	i = -1;
	current = g_shell_tmp_vars;
	while (current)
	{
		if ((res[++i] = job_join_tmpvar_def(current)) == NULL)
		{
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
			while (i-- > 0)
				ft_strdel(&(res[i]));
			ft_memdel((void **)&(res));
		}
		current = current->next;
	}
	while (res && ++i < s_tmp + s_env)
		if ((res[i] = ft_strdup(env[i - s_tmp])) == NULL)
		{
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
			while (i-- > 0)
				ft_strdel(&(res[i]));
			ft_memdel((void **)&(res));
		}
	return (res);
}

/*
**	This function creates a new environment definition based on the shell's
**	current environment (stored in 'env') AND its current temporary variables
**	(stored 'g_in shell_tmp_vars')
**	It first counts the number of TMP variables and the number of ENVIRON
**	elements to allocate the new array correctly
**	The function 'job_fill_with_env_and_tmp' is then called to fill said array
**
**	Arguments:
**	env (char **) -> The shell's current environment definition
**
**	Return Value (char **):
**	NULL -> An malloc error occured
**	NON-NULL -> The newly allocated array contaiing both the environment and
**		the TMP variables
*/

char			**job_join_env_tmpvars(char **env)
{
	size_t	s_env;
	size_t	s_tmp;
	char	**res;

	s_env = job_env_depth(env);
	s_tmp = job_tmpvars_list_depth();
	if ((res = ft_memalloc((s_env + s_tmp + 1) * sizeof(char *))) == NULL)
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (NULL);
	}
	res = job_fill_with_env_and_tmp(res, env, s_env, s_tmp);
	res[s_env + s_tmp] = NULL;
	return (res);
}
