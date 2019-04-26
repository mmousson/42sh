# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    line_edition.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 11:51:22 by mmousson          #+#    #+#              #
#    Updated: 2019/04/26 13:39:55 by roliveir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LINE_EDIT_PATH = ./src/line_edition/
VIMODE_PATH = $(LINE_EDIT_PATH)vi_mode/

VIMODE =	alloc_vi.c			\
			getvi_keys.c		\
			setmode.c			\
			vi_command.c		\
			vi_edition.c		\
			jump_occur.c		\
			vi_cdel.c			\
			vi_com_motion.c		\
			vi_delete.c			\
			vi_history.c		\
			vi_insert.c			\
			vi_paste.c			\
			vi_repeat.c			\
			vi_undo.c			\
			vi_visual.c			\
			vi_yank.c			\
			jump_vi_manager.c

LINE_EDIT =	cpy.c				\
			cursor_motion.c		\
			del_env.c			\
			get_keys.c			\
			history.c			\
			isalt.c				\
			jump_words.c		\
			line_alloc.c		\
			line_edition.c		\
			line_read_notty.c	\
			line_read.c			\
			print_line.c		\
			reset_cursor.c		\
			term_manager.c		\
			coordinates_calc.c	\
			termcaps.c			\
			isctrl_motion.c

LINE_EDIT_SRCS = $(addprefix $(LINE_EDIT_PATH),$(LINE_EDIT))
VIMODE_SRCS = $(addprefix $(VIMODE_PATH),$(VIMODE))
SRCS += $(LINE_EDIT_SRCS)
SRCS += $(VIMODE_SRCS)

