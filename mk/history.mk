# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    history.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 10:06:21 by roliveir          #+#    #+#              #
#    Updated: 2019/06/18 15:03:43 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HIST_PATH = ./src/history/
HIST_NAME = hist_main.c			\
			hist_alloc.c		\
			hist_parser.c		\
			hist_expend.c		\
			hist_search.c		\
			hist_utils.c		\
			hist_must_skip_cmd.c

HIST_SRCS = $(addprefix $(HIST_PATH),$(HIST_NAME))
SRCS += $(HIST_SRCS)
