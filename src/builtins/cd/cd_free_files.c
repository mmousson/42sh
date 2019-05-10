/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_free_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 03:17:08 by tduval            #+#    #+#             */
/*   Updated: 2019/05/04 03:22:29 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*cd_free_files(char **files)
{
	int		i;

	i = 0;
	while (files && files[i])
	{
		ft_strdel(&files[i]);
		i++;
	}
	ft_memdel((void **)&files);
	return (NULL);
}
