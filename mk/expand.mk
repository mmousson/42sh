# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    expand.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/22 12:16:40 by oboutrol          #+#    #+#              #
#    Updated: 2019/06/03 00:54:03 by oboutrol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXPAND_PATH = ./src/expand/
EXPAND_NAME =	expand_manager.c			\
				expand_shell_param.c		\
				expand_param.c				\
				expand_curly.c				\
				expand_insert_word.c		\
				expand_filename.c			\
				expand_spec_param.c			\
				expand_arithmetic/expand_arithmetic.c 	\
				expand_arithmetic/computor/calcul.c \
				expand_arithmetic/computor/compute.c \
				expand_arithmetic/computor/crementation.c \
				expand_arithmetic/computor/logical.c \
				expand_arithmetic/parser/ast/build_ast.c \
				expand_arithmetic/parser/ast/fill_node.c \
				expand_arithmetic/parser/ast/precedence.c \
				expand_arithmetic/parser/ast/tools.c \
				expand_arithmetic/parser/checker/checker.c \
				expand_arithmetic/parser/checker/grammar/check_expression.c \
				expand_arithmetic/parser/checker/grammar/check_number.c \
				expand_arithmetic/parser/checker/grammar/check_operande.c \
				expand_arithmetic/parser/checker/grammar/check_operator.c \
				expand_arithmetic/parser/checker/grammar/check_sub_expression.c\
				expand_arithmetic/parser/checker/grammar/check_variable.c \
				expand_arithmetic/parser/checker/grammar/check_token.c \
				expand_arithmetic/parser/lexer/delimitor.c \
				expand_arithmetic/parser/lexer/lexer.c \
				expand_arithmetic/tools/skip_spaces.c \
				expand_arithmetic/tools/ast.c \
				expand_arithmetic/tools/token.c \
				expand_token.c				\
				expand_curly_tool.c			\
				expand_tild.c				\
				expand_tild_unit.c			\
				expand_param_glob.c			\
				expand_question.c			\
				expand_quote_removal.c		\
				expand_param/expand_substring/remove_substring/remove_substring.c \
				expand_param/expand_substring/remove_substring/tokenize.c \
				expand_param/expand_substring/remove_substring/match_pattern.c

EXPAND_SRCS = $(addprefix $(EXPAND_PATH),$(EXPAND_NAME))
SRCS += $(EXPAND_SRCS)
