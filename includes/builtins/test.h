/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 08:13:04 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 09:04:19 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "libft.h"
# include "sh42.h"

# define TEST_TRUE 0
# define TEST_FALSE 1
# define TEST_ERROR 2

# define UNARY_TABLE_LEN 15
# define BINARY_TABLE_LEN 8

typedef struct		s_unary_matcher
{
	char				*unary_name;
	int					(*handler) (char *string);
}						t_unary_matcher;

typedef struct			s_binary_matcher
{
	char				*binary_name;
	int					(*handler) (char *one, char *two);
}						t_binary_matcher;

extern t_unary_matcher	g_unary_table[];
extern t_binary_matcher	g_binary_table[];

int						two_args(int argc, char **argv);
int						three_args(int argc, char **argv);
int						four_args(int argc, char **argv);

#endif
