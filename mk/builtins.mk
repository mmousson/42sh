# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    builtins.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 11:49:45 by mmousson          #+#    #+#              #
#    Updated: 2019/04/26 11:49:46 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BUILTINS_PATH = ./src/builtins/
BUILTINS =	alias.c										\
			bg.c										\
			cd.c										\
			echo.c										\
			export.c									\
			fg.c										\
			ft_exit.c									\
			hash/hash.c									\
			hash/add_hash_entry.c						\
			hash/init_hash_table.c						\
			jobs/jobs.c									\
			jobs/parse_options.c						\
			jobs/jobs_format_msg.c						\
			set.c										\
			test/binary_primary/equality_comparison.c	\
			test/binary_primary/magnitude_comparison.c	\
			test/unary_primary/check_type.c				\
			test/unary_primary/string_len.c				\
			test/two_argc.c								\
			test/three_argc.c							\
			test/four_argc.c							\
			test/test_builtin.c							\
			type.c										\
			unalias.c									\
			unset.c

BUILTINS_SRCS = $(addprefix $(BUILTINS_PATH),$(BUILTINS))
SRCS += $(BUILTINS_SRCS)
