# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lexer.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/06 20:29:33 by oboutrol          #+#    #+#              #
#    Updated: 2019/06/14 15:16:32 by oboutrol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEXER_PATH = ./src/lexer/
LEXER_NAME =	lex_init.c				\
			 	lex.c					\
			 	lex_get_ch.c			\
			 	lex_more.c				\
				lex_exclam.c			\
			 	lex_add_char.c			\
				lex_back_slash_quote.c	\
			 	lex_print_state.c		\
			 	lex_process.c			\
			 	lex_free_stat.c			\
				lex_include.c			\
				lex_welding.c			\
			 	lex_free_token.c		\
				lex_print_stack.c		\
				lex_store.c				\
				lex_store_dol.c			\
				lex_add_arg_token.c		\
				lex_store_error.c		\
			 	lex_get_state.c

LEXER_SRCS = $(addprefix $(LEXER_PATH),$(LEXER_NAME))
SRCS += $(LEXER_SRCS)
