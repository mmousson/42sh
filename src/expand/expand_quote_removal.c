/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:33:13 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/26 16:11:11 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NONE 0
#define DOUBLE 1
#define SIMPLE 2

static void	process_dbquote(int *mod, int *forward, int *over)
{
	if (!(*mod))
	{
		*mod = DOUBLE;
		(*forward)++;
	}
	else if (*mod == DOUBLE)
	{
		*mod = NONE;
		(*forward)++;
	}
	else if (*mod == SIMPLE)
		(*over)++;
}

static void	process_spquote(int *mod, int *forward, int *over)
{
	if (!(*mod))
	{
		*mod = SIMPLE;
		(*forward)++;
	}
	else if (*mod == DOUBLE)
		(*over)++;
	else if (*mod == SIMPLE)
	{
		*mod = NONE;
		(*forward)++;
	}
}

static void	process_back_slash(int *mod, int *forward, int *over, char *str)
{
	char	esc;

	esc = str[(*over + *forward + 1)];
	if (*mod == SIMPLE)
		(*over)++;
	else if (esc == '"' || esc == '\\' || (!(*mod) && esc == '\''))
	{
		str[*over] = esc;
		(*over)++;
		(*forward)++;
	}
	else if (esc == '\n')
	{
		*forward += 2;
	}
	else
		(*forward)++;
}

static int	remove_quote(char *str)
{
	int		over;
	int		forward;
	int		mod;

	over = 0;
	forward = 0;
	mod = NONE;
	while (str[over + forward])
	{
		if (str[over + forward] == '"')
			process_dbquote(&mod, &forward, &over);
		else if (str[over + forward] == '\'')
			process_spquote(&mod, &forward, &over);
		else if (str[over + forward] == '\\')
			process_back_slash(&mod, &forward, &over, str);
		else
			over++;
		str[over] = str[over + forward];
	}
	str[over] = 0;
	return (0);
}

int			expand_quote_removal(char ***argv)
{
	char	*str;
	int		k;

	if (!argv || !*argv)
		return (1);
	k = 0;
	while ((str = ((*argv)[k])))
	{
		if (remove_quote(str))
			return (1);
		k++;
	}
	return (0);
}
