/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_subshell_signal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:47:26 by mmousson          #+#    #+#             */
/*   Updated: 2019/07/03 18:16:55 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "sh42.h"
#include "line_edition.h"

void	job_subshell_signal(int signo)
{
	static const char	*exit_args[3] = {"exit", "126", NULL};

	if (signo == SIGUSR1)
		blt_exit(2, (char **)exit_args, g_env.env);
}
