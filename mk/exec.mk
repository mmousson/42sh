# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    exec.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/06 20:38:11 by oboutrol          #+#    #+#              #
#    Updated: 2019/05/08 18:23:42 by oboutrol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC_PATH = ./src/exec/

EXEC_NAME = 	ft_exec.c\
				ft_exec_tool.c\
				ft_launch_cmd.c\
				exe_init.c\
				ft_split_path.c\
				ft_free_exe.c\
				ft_pipe_close.c\
				exe_error.c\
				exe_add_red.c\
				ft_launch_red.c\
				ft_heredoc.c\
				ft_tabdup.c\
				ft_launch_pipe.c\
				ft_pile.c\
				ft_getenv.c\
				exec_cmd.c\
				ft_expend.c\
				ft_expend_tool.c\
				exe_load.c\
				exe_print_job.c\
				built_manager.c\
				ft_path.c

EXEC_SRCS = $(addprefix $(EXEC_PATH),$(EXEC_NAME))
SRCS += $(EXEC_SRCS)
