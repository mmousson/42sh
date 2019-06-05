/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 10:20:21 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/05 04:28:01 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include <dirent.h>
# include "sh42.h"
# include "libft.h"

# define ALIAS 0
# define BUILTIN 1
# define BINARY 2
# define NOT_FOUND 3

char	*alias_exists(char *token);

#endif
