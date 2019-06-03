/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_question.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 23:09:50 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/02 23:16:11 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "libft.h"

int			expand_question(char *var, const char *str, char ***arge)
{
	char	*res;

	if ((res = take_word_expand(str + 2, arge)) && res[0])
	{
		ft_putstr_fd("42sh: ",2 );
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(res, 2);
		ft_putstr_fd("\n", 2);
		free(res);
	}
	else
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": parameter null or not set\n", 2);
	}
	return (0);
}
