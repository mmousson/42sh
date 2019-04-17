/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 21:34:07 by oboutrol          #+#    #+#             */
/*   Updated: 2019/03/19 02:44:29 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include "libft.h"
#include <stdlib.h>

char		*ft_strpaste(char *str, char c)
{
	int		len;
	char	*ret;
	int		k;

	k = 0;
	if (!(str))
		len = 0;
	else
		len = ft_strlen(str);
	if (!(ret = (char*)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	while (str && str[k])
	{
		ret[k] = str[k];
		k++;
	}
	ret[k] = c;
	ret[k + 1] = '\0';
	if (str)
		free(str);
	return (ret);
}

int			ft_comp_word(t_cmd *cmd, char k)
{
	t_word	*tmp;
	t_word	*target;

	target = ft_target(cmd);
	tmp = target;
	if (!target)
		if (!(target = init_word()))
			return (1);
	while (target->next)
		target = target->next;
	if (target->news == 1)
		ft_add_word(cmd, k);
	else if (!(target->value = ft_strpaste(target->value, k)))
		return (1);
	target = tmp;
	return (0);
}

int			ft_starg(t_args *args)
{
	t_cmd	*tmp_c;

	tmp_c = args->cmd;
	while (args->cmd && args->cmd->next)
		args->cmd = args->cmd->next;
	if (args->cmd && args->str)
		if (ft_comp_word(args->cmd, args->str[args->k]))
			return (1);
	args->cmd = tmp_c;
	return (0);
}
