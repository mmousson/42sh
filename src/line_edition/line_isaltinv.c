/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_isaltinv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:17:13 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/05 16:31:09 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			line_isaltt(char *str, int ret)
{
	if (ret == 3 && str[0] == -30 && str[1] == -128 && str[2] == -96)
		return (1);
	return (0);
}	
