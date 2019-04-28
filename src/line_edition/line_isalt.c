/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_isalt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 02:47:52 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/28 12:33:42 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				line_isaltc(char *str, int ret)
{
	if (ret == 2 && str[0] == -61 && str[1] == -89)
		return (1);
	return (0);
}

int				line_isaltx(char *str, int ret)
{
	if (ret == 3 && str[0] == -30 && str[1] == -119 && str[2] == -120)
		return (1);
	return (0);
}

int				line_isaltv(char *str, int ret)
{
	if (ret == 3 && str[0] == -30 && str[1] == -120 && str[2] == -102)
		return (1);
	return (0);
}

int				line_isaltf(char *str, int ret)
{
	if (ret == 2 && str[0] == -58 && str[1] == -110)
		return (1);
	return (0);
}

int				line_isaltb(char *str, int ret)
{
	if (ret == 3 && str[0] == -30 && str[1] == -120 && str[2] == -85)
		return (1);
	return (0);
}
