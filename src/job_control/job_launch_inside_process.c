/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_launch_inside_process.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:29:16 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/27 11:32:14 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "sh42.h"
#include "job_control_42.h"

void	job_launch_inside_process(int blt_pos, t_job *job, t_process *pr)
{
	job->pgid = 0;
	job_open_files(pr);
	job_builtin_redirect(pr);
	if (pr->compound)
		pr->status = !lex_str(&(pr->compound_command), pr->environ);
	else
		pr->status = g_builtins[blt_pos].handler(job_argc(pr->argv),
		pr->argv, pr->environ);
	pr->completed = true;
	pr->valid_to_wait_for = false;
	job_builtin_restore(pr);
}
