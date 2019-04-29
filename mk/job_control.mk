# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    job_control.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 11:56:59 by mmousson          #+#    #+#              #
#    Updated: 2019/04/29 22:36:13 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

JOB_CTRL_PATH = ./src/job_control/

JOB_CTRL =	job_initialize.c					\
			job_child_process.c					\
			job_parent_process.c				\
			job_command_search_and_exec.c		\
			job_engine.c						\
			job_foreground.c					\
			job_background.c					\
			job_mark_process_status.c			\
			job_update_job_status.c				\
			job_search_utility.c				\
			job_sig_table.c						\
			job_sigchld_handler.c				\
			job_utility.c

JOB_CTRL_SRCS = $(addprefix $(JOB_CTRL_PATH),$(JOB_CTRL))
SRCS += $(JOB_CTRL_SRCS)
