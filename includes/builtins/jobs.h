/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:38:08 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/12 10:32:45 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_H
# define JOBS_H

# include <stdlib.h>
# include "libft.h"
# include "job_control_42.h"

# define ALLOWED_OPTIONS "lp"
# define JOBS_L_INDEX 0
# define JOBS_P_INDEX 1

# define JOBS_OK 0
# define JOBS_ERROR 1
# define JOBS_INVALID_OPTION 2

int			parse_options(int argc, char **argv, int *parsed);
void		format_job_info(t_job *head, int options, int i);

#endif
