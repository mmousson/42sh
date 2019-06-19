/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:43:02 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/06 13:44:30 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_cdenv(char *cdenv[4])
{
	ft_strdel(&cdenv[0]);
	ft_strdel(&cdenv[1]);
	ft_strdel(&cdenv[2]);
	ft_strdel(&cdenv[3]);
}

void	free_cd_tabs(char **tmp, char **nenv, char **narg)
{
	ft_strtabdel(&tmp);
	ft_strtabdel(&nenv);
	if (narg[0])
		ft_strdel(&narg[0]);
	if (narg[1])
		ft_strdel(&narg[1]);
	if (narg[2])
		ft_strdel(&narg[2]);
	free(narg);
}

char	*ft_strjointab(char **arr, char sep)
{
	int		i;
	int		len;
	char	*result;
	char	sepp[2];

	i = -1;
	len = 0;
	sepp[0] = sep;
	sepp[1] = '\0';
	if (arr == NULL || !arr[0])
		return (ft_strdup(sepp));
	while (arr[++i])
		len += ft_strlen(arr[i]);
	len += i;
	if (!(result = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		ft_strcat(result, sepp);
		ft_strcat(result, arr[i]);
	}
	return (result);
}
