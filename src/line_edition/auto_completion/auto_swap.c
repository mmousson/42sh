/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 12:21:36 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/20 11:47:28 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void			auto_swapstr(char **a, char **b)
{
	char		*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void			auto_swapint(int *a, int *b)
{
	int			tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void			auto_swapchar(char *a, char *b)
{
	char		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
