/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:32:25 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/16 21:41:53 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

void		ft_pipe_close(int *fdpipe, int nbr_pipes)
{
	int		k;

	k = 0;
	while (k < 2 * nbr_pipes)
	{
		close(fdpipe[k]);
		k++;
	}
}

int			ft_end_of_pipes(int *fdpipe, int nbr_pipes)
{
	int		end;
	int		status;

	status = -2;
	ft_pipe_close(fdpipe, nbr_pipes);
	end = 0;
	while (end <= nbr_pipes)
	{
		wait(&status);
		end++;
	}
	return (nbr_pipes);
}
