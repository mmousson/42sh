/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:07:58 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 04:55:45 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "sh42.h"
# include "libft.h"

# define HASH_OK 0
# define HASH_ERROR 1
# define HASH_NO_SUCH_OPTION 2

int	hash_string(char *string);

#endif
