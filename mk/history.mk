# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    history.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roliveir <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 10:06:21 by roliveir          #+#    #+#              #
#    Updated: 2019/05/14 17:35:35 by roliveir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HIST_PATH = ./src/history/
HIST_NAME = hist_main.c			\
			hist_alloc.c		\
			hist_parser.c		\
			hist_expend.c

HIST_SRCS = $(addprefix $(HIST_PATH),$(HIST_NAME))
SRCS += $(HIST_SRCS)
