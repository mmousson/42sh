/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 02:47:52 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/26 11:36:55 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				ft_isaltc(char *str, int ret)
{
	if (str[0] == -61 && str[1] == -89 && ret == 2)
		return (1);
	return (0);
}

int				ft_isaltx(char *str, int ret)
{
	if (str[0] == -30 && str[1] == -119 && str[2] == -120 && ret == 3)
		return (1);
	return (0);
}

int				ft_isaltv(char *str, int ret)
{
	if (str[0] == -30 && str[1] == -120 && str[2] == -102 && ret == 3)
		return (1);
	return (0);
}

int				ft_isaltf(char *str, int ret)
{
	if (str[0] == -58 && str[1] == -110 && ret == 2)
		return (1);
	return (0);
}

int				ft_isaltb(char *str, int ret)
{
	if (str[0] == -30 && str[1] == -120 && str[2] == -85 && ret == 3)
		return (1);
	return (0);
}
