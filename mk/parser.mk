# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    parser.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/06 20:35:29 by oboutrol          #+#    #+#              #
#    Updated: 2019/05/28 17:46:22 by oboutrol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSER_PATH = ./src/parser/

PARSER_NAME =	pars.c					\
				pars_prepars.c			\
				pars_line.c				\
				pars_select_pars.c		\
				pars_cleans_spa.c		\
				pars_cmd.c				\
				pars_pipe.c				\
				pars_word.c				\
				pars_nword.c			\
				pars_part.c				\
				pars_red.c				\
				pars_tool.c				\
				expand_arith.c			\
				pars_print_tree.c		\
				free_tree.c				\
				pars_is_delimiter.c		\
				pars_work_tree.c

PARSER_SRCS = $(addprefix $(PARSER_PATH), $(PARSER_NAME))
SRCS += $(PARSER_SRCS)
