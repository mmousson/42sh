# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    option.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roliveir <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/28 08:35:38 by roliveir          #+#    #+#              #
#    Updated: 2019/05/28 18:55:21 by roliveir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OPT_PATH = ./src/line_edition/auto_completion/option_text/
OPT_NAME = 	option_ls.c		\
		option_cat.c		\
		option_date.c		\
		option_chmod.c		\
		option_cp.c			\
		option_df.c			\
		option_echo.c		\
		option_kill.c		\
		option_ln.c			\
		option_mkdir.c		\
		option_pax.c		\
		option_ps.c			\
		option_rm.c			\
		option_stty.c		\
		option_cd.c			\
		option_export.c		\
		option_hash.c		\
		option_jobs.c		\
		option_set.c		\
		option_test.c		\
		option_type.c		\
		option_unalias.c	\
		option_unset.c		\
		option_fc.c

OPT_SRCS = $(addprefix $(OPT_PATH),$(OPT_NAME))
SRCS += $(OPT_SRCS)
