/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charac.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 00:21:32 by oboutrol          #+#    #+#             */
/*   Updated: 2019/03/30 06:21:56 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include "libft.h"

int		ft_charac(char k)
{
	if (k >= '0' && k <= '9')
		return (INT);
	else if (k == ' ' || k == '\t')
		return (SPACE);
	else if (k == '\n' || k == ';')
		return (CMDEND);
	else if (k == '|')
		return (PIPE);
	else if (k == '\0')
		return (END);
	else if (k == '<')
		return (INF);
	else if (k == '>')
		return (SUP);
	else if (k == '"')
		return (QT_DB);
	else if (k == '\'')
		return (QT_SP);
	else if (k == '&')
		return (EPERL);
	else if (k == '-')
		return (SEG);
	else
		return (CHAR);
}
