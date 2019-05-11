# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    line_edition.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 11:51:22 by mmousson          #+#    #+#              #
#    Updated: 2019/05/10 13:34:25 by roliveir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LINE_EDIT_PATH = ./src/line_edition/
VIMODE_PATH = $(LINE_EDIT_PATH)vi_mode/
AUTOCMP_PATH = $(LINE_EDIT_PATH)auto_completion/
PROMPT_PATH = $(LINE_EDIT_PATH)classic_prompt/

VIMODE =	vi_alloc.c							\
			vi_getkeys.c						\
			vi_setmode.c						\
			vi_command.c						\
			vi_count.c							\
			vi_jumpoccur.c						\
			vi_cdel.c							\
			vi_com_motion.c						\
			vi_delete.c							\
			vi_history.c						\
			vi_insert.c							\
			vi_paste.c							\
			vi_repeat.c							\
			vi_undo.c							\
			vi_visual.c							\
			vi_yank.c							\
			vi_jump_manager.c					\
			vi_prior_flag.c						\
			vi_alloc_replace.c					\
			vi_alloc_count.c

PROMPT =	prompt_classic.c					\
			prompt_format_path.c				\
			prompt_get_additions_deletions.c	\
			prompt_git_branch.c					\

LINE_EDIT =	line_cpy.c							\
			line_curmotion.c					\
			line_delenv.c						\
			line_getkeys.c						\
			line_history.c						\
			line_del.c							\
			line_isalt.c						\
			line_jumpwords.c					\
			line_alloc.c						\
			line_edition.c						\
			line_read_notty.c					\
			line_read.c							\
			line_print.c						\
			line_resetcurs.c					\
			line_term.c							\
			line_calc.c							\
			line_termcaps.c						\
			line_iskeymotion.c					\
			line_iskeydel.c						\
			line_quit.c							\
			line_cxjump.c						\
			line_undo.c							\
			line_inverse.c						\
			line_isaltinv.c

AUTOCMP =	auto_main.c				\
			auto_utils.c			\
			auto_getype.c			\
			auto_alloc.c			\
			auto_print.c			\
			auto_alloc_wordlst.c	\
			auto_choose.c			\
			auto_termcaps.c			\
			auto_getstatinfo.c

LINE_EDIT_SRCS = $(addprefix $(LINE_EDIT_PATH),$(LINE_EDIT))
VIMODE_SRCS = $(addprefix $(VIMODE_PATH),$(VIMODE))
AUTOCMP_SRCS = $(addprefix $(AUTOCMP_PATH),$(AUTOCMP))
PROMPT_SRCS = $(addprefix $(PROMPT_PATH),$(PROMPT))
SRCS += $(LINE_EDIT_SRCS)
SRCS += $(VIMODE_SRCS)
SRCS += $(AUTOCMP_SRCS)
SRCS += $(PROMPT_SRCS)
