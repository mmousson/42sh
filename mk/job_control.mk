# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    job_control.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 11:56:59 by mmousson          #+#    #+#              #
#    Updated: 2019/04/26 13:33:29 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

JOB_CTRL_PATH = ./src/job_control/

JOB_CTRL =	initialize.c					\
			child_process.c					\
			parent_process.c				\
			job_engine.c					\
			job_command_search_and_exec.c	\
			foreground.c					\
			background.c					\
			mark_process_status.c			\
			update_job_status.c				\
			search_utility.c				\
			sig_table.c						\
			sigchld_handler.c				\
			utility.c

JOB_CTRL_SRCS = $(addprefix $(JOB_CTRL_PATH),$(JOB_CTRL))
SRCS += $(JOB_CTRL_SRCS)
