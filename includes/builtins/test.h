/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 08:13:04 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/11 13:07:22 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <sys/stat.h>
# include "libft.h"
# include "sh42.h"

/*
**	Possible return values for 'test' builtin command
*/

# define TEST_TRUE 0
# define TEST_FALSE 1
# define TEST_ERROR 2
# define IGNORE_TYPE 1
# define CHECK_SIZE 12

/*
**	Set the length of the two dispatchers used by 'test' utility
**	UNARY_TABLE_LEN for unary comparison
**	UNARY_TABLE_LEN for binary comparison
*/

# define UNARY_TABLE_LEN 16
# define BINARY_TABLE_LEN 8

/*
**	Structure used to define the 'unary' comparison dispatcher
**	unary_name -> The string representing the actual unary comparator
**		(i.e: -b)
**	handler -> Function pointer that will handle the comparison of the
**		corresponding unary comparator
*/

typedef struct			s_unary_matcher
{
	char				*unary_name;
	int					(*handler) (const char *str, const unsigned int mask);
	int					mask;
}						t_unary_matcher;

/*
**	Structure used to define the 'binary' comparison dispatcher
**	unary_name -> The string representing the actual binary comparator
**		(i.e: -lt)
**	handler -> Function pointer that will handle the comparison of the
**		corresponding binary comparator
*/

typedef struct			s_binary_matcher
{
	char				*binary_name;
	int					(*handler) (const char *one, const char *two);
}						t_binary_matcher;

/*
**	Define the dispatchers as 'extern' so every file can access them
**	when needed
*/

extern t_unary_matcher	g_unary_table[];
extern t_binary_matcher	g_binary_table[];

/*
**	==================== MAIN 'TEST' FUNCTIONS ====================
**	two_args -> builtins/test/two_argc.c
**	three_args -> builtins/test/three_argc.c
**	four_args -> builtins/test/four_argc.c
**	integer_expected -> builtins/test/binary_primary/equality_comparison.c
*/

int						two_args(char **a);
int						three_args(char **argv);
int						four_args(char **argv);
int						integer_expected(const char *s);

/*
**	Binary function comparators
**	test_eq (-eq) -> buitlins/test/binary_primary/equality_comparison.c
**	test_ne (-ne) -> buitlins/test/binary_primary/equality_comparison.c
**	test_gt (-gt) -> buitlins/test/binary_primary/magnitude_comparison.c
**	test_ge (-ge) -> buitlins/test/binary_primary/magnitude_comparison.c
**	test_lt (-lt) -> buitlins/test/binary_primary/magnitude_comparison.c
**	test_le (-le) -> buitlins/test/binary_primary/magnitude_comparison.c
*/

int						test_eq(const char *n1, const char *n2);
int						test_ne(const char *n1, const char *n2);
int						test_gt(const char *n1, const char *n2);
int						test_ge(const char *n1, const char *n2);
int						test_lt(const char *n1, const char *n2);
int						test_le(const char *n1, const char *n2);

/*
**	Unary function comparators
**	test_z (-z) -> builtins/test/unary_primary/string_len.c
**	test_n (-n) -> builtins/test/unary_primary/string_len.c
**	test_files (-bcdefgLprSsuwxz) -> builtins/test/unary_primary/test_files.c
*/

int						test_z(const char *string, const unsigned int mask);
int						test_n(const char *string, const unsigned int mask);
int						check_type(const char *pathname,
	const unsigned int bitmask);

#endif
