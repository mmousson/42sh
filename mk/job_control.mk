# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    job_control.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 11:56:59 by mmousson          #+#    #+#              #
#    Updated: 2019/06/11 17:40:25 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

JOB_CTRL_PATH = ./src/job_control/

JOB_CTRL =	job_initialize.c					\
			job_add_to_active_jobs.c			\
			job_bad_fd_notifier.c				\
			job_builtin_redirect.c				\
			job_check_variable_declaration.c	\
			job_child_process.c					\
			job_free.c							\
			job_parent_process.c				\
			job_drop_unnecessary_processes.c	\
			job_command_search_and_exec.c		\
			job_engine.c						\
			job_foreground.c					\
			job_background.c					\
			job_mark_process_status.c			\
			job_join_env_tmpvars.c				\
			job_update_job_status.c				\
			job_search_utility.c				\
			job_sig_table.c						\
			job_sigchld_handler.c				\
			job_utility.c

JOB_CTRL_SRCS = $(addprefix $(JOB_CTRL_PATH),$(JOB_CTRL))
SRCS += $(JOB_CTRL_SRCS)
