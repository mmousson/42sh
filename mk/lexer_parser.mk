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

LEXER =		lex.c					\
			lex_add_char.c			\
			lex_get_ch.c			\
			lex_get_state.c			\
			lex_init.c				\
			lex_more.c				\
			lex_print_state.c		\
			lex_process.c

PARSER =	pars.c					\
			pars_cleans_spa.c		\
			pars_line.c				\
			pars_cmd.c				\
			pars_nword.c			\
			pars_part.c				\
			pars_pipe.c				\
			pars_print_tree.c		\
			pars_red.c				\
			pars_rer_lr.c			\
			pars_select_pars.c		\
			pars_tool_pars.c		\
			pars_word.c				\
			pars_work_tree.c

LEXER_SRCS = $(addprefix $(LEXER_PATH),$(LEXER))
PARSER_SRCS = $(addprefix $(PARSER_PATH),$(PARSER))
SRCS += $(LEXER_SRCS)
SRCS += $(PARSER_SRCS)
