# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    expand.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/22 12:16:40 by oboutrol          #+#    #+#              #
#    Updated: 2019/05/28 10:26:24 by oboutrol         ###   ########.fr        #
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
				expand_token.c				\
				expand_quote_removal.c

EXPAND_SRCS = $(addprefix $(EXPAND_PATH),$(EXPAND_NAME))
SRCS += $(EXPAND_SRCS)
