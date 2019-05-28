/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:06:32 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 17:51:29 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETIC_H
# define ARITHMETIC_H

#include <stdlib.h>

# define NUMBER				11
# define VARIABLE			12
# define INVALID			13

# define DOUBLEAND			0x2626
# define DOUBLEPIPE			0x7C7C
# define DOUBLEEQUAL		0x3D3D
# define LESS				0x3C
# define GREAT				0x3E
# define BANGEQUAL			0x3D21
# define LESSEQUAL			0x3D3C
# define GREATEQUAL			0x3D3E
# define DOUBLEPLUS			0x2B2B
# define DOUBLEMINUS		0x2D2D

# define PLUS				0x2B
# define MINUS				0x2D
# define STAR				0x2A
# define PERCENT			0x25
# define SLASH				0x2F

# define OP_PAR				0x28
# define CL_PAR				0x29
# define BANG				0x21

typedef struct				s_arithtok
{
	char					*val;
	size_t					length;
	int						type;
	int						valid;
	struct s_arithtok		*next;
}							t_arithtok;

typedef struct				s_arithast
{
	t_arithtok				*token;
	t_arithtok				*left_arg;
	t_arithtok				*right_arg;
	struct s_arithast		*left;
	struct s_arithast		*right;
}							t_arithast;

int				arithmetic(char ***env, long *res, char *str);
int				compute_operation(char ***env, char *exp,
				t_arithast *ast, long *res);
int				compute_division(char ***env, char *exp,
				t_arithast *ast, long *res);
int				compute_variable(char ***env, t_arithast *ast, long *res);
int				compute_number(t_arithast *ast, long *res);
int				compute(char ***env, char *exp, t_arithast *ast, long *res);
int				compute_crementation(char ***env, t_arithast *ast, long *res);
int				compute_logical(char ***env, char *exp, t_arithast *ast, long *res);
int				compute_inverse(char ***env, char *exp, t_arithast *ast, long *res);
int				arith_build_ast(t_arithast **ast, t_arithtok **token);
int				arith_fill_node(t_arithast **ast, t_arithtok **chosen);
int				arith_get_rank(int type);
void			routine_tok(t_arithtok **token, t_arithtok **primary,
				t_arithtok **primary_prev);
t_arithtok		*arith_get_primary_prev_token(t_arithtok **primary_prev,
				t_arithtok *token);
void			arith_remove_parentheses(t_arithtok **tok);
int				arith_div_zero_error(char *expr, t_arithtok *tok);
int				arith_value_base_error(t_arithtok *begin, t_arithtok *tok);
int				arith_syntax_error(char *expr, t_arithtok *tok, int err);
t_arithtok		*check_expression_lex(t_arithtok *token, int *err);
int				check_expression(char *expr, t_arithtok *token);
int				check_is_expression(t_arithtok **tok);
int				check_is_number(t_arithtok **tok);
int				check_number_base(char *s);
int				check_is_operande(t_arithtok **tok);
int				check_is_comparison_op(t_arithtok **tok);
int				check_is_calcul_op(t_arithtok **tok);
int				check_is_operator(t_arithtok **tok);
int				check_is_sub_expression(t_arithtok **tok);
int				check_is_variable(t_arithtok **tok);
t_arithtok		*arith_get_crement_arithtok(char **line);
t_arithtok		*arith_get_variable_token(char **line, int check_post_crement);
t_arithtok		*compare_operator(char **line, int type, int test, int size);
t_arithtok		*arith_get_operators_token(char **line);
void			arith_lexical_analysis(t_arithtok **token, char *line);
void			astlist_del(t_arithast **ast);
void			tokenlist_del(t_arithtok **token);
char			*walkparenthese(char *s);
void			arith_skip_spaces(char **line);
int				arith_isspace(char c);
t_arithtok		*token_dup(t_arithtok *tok);
t_arithtok		*token_new(char *val, size_t length, int type, t_arithtok *next);
void			token_del(t_arithtok **tok);
int				check_token(t_arithtok **tok, int type);

#endif