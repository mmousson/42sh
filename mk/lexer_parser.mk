# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lexer_parser.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 11:51:08 by mmousson          #+#    #+#              #
#    Updated: 2019/04/26 11:51:08 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEXER_PATH = ./src/lexer/
PARSER_PATH = ./src/parser/

LEXER =		lex.c				\
			process.c			\
			ft_init.c			\
			get_ch.c			\
			more.c				\
			add_char.c			\
			print_state.c		\
			get_state.c

PARSER =	pars.c				\
			pars_line.c			\
			ft_select_pars.c	\
			ft_cleans_spa.c		\
			pars_cmd.c			\
			pars_pipe.c			\
			pars_word.c			\
			pars_nword.c		\
			pars_part.c			\
			pars_red.c			\
			pars_rer_lr.c		\
			tool_pars.c			\
			print_tree.c		\
			work_tree.c

LEXER_SRCS = $(addprefix $(LEXER_PATH),$(LEXER))
PARSER_SRCS = $(addprefix $(PARSER_PATH),$(PARSER))
SRCS += $(LEXER_SRCS)
SRCS += $(PARSER_SRCS)
