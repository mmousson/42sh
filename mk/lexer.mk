# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lexer.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/06 20:29:33 by oboutrol          #+#    #+#              #
#    Updated: 2019/05/13 10:18:31 by roliveir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEXER_PATH = ./src/lexer/
LEXER_NAME =	lex_init.c			\
			 	lex.c				\
			 	lex_get_ch.c		\
			 	lex_more.c			\
			 	lex_add_char.c		\
			 	lex_print_state.c	\
			 	lex_process.c		\
			 	ft_free_stat.c		\
			 	ft_free_token.c		\
			 	lex_get_state.c

LEXER_SRCS = $(addprefix $(LEXER_PATH),$(LEXER_NAME))
SRCS += $(LEXER_SRCS)
