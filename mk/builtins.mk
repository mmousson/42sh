# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    builtins.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 11:49:45 by mmousson          #+#    #+#              #
#    Updated: 2019/06/04 12:34:09 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BUILTINS_PATH = ./src/builtins/
BUILTINS =	builtin_alias.c									\
			builtin_bg.c									\
			cd/build_pwd_tab.c								\
			cd/builtin_cd.c									\
			cd/flags.c										\
			cd/get_final_path.c								\
			cd/get_pwd_for_cd.c								\
			cd/utils_cd.c									\
			builtin_echo.c									\
			builtin_exit.c									\
			builtin_export.c								\
			builtin_fg.c									\
			builtin_set.c									\
			builtin_type.c									\
			builtin_unalias.c								\
			builtin_unset.c									\
			builtin_history.c								\
			fc/builtin_fc.c									\
			fc/parse.c										\
			fc/read_args.c									\
			fc/set_default_values.c							\
			fc/free_memory.c								\
			hash/hash.c										\
			hash/hash_add_hash_entry.c						\
			hash/hash_init_hash_table.c						\
			jobs/jobs.c										\
			jobs/jobs_parse_options.c						\
			jobs/jobs_format_msg.c							\
			test/binary_primary/test_equality_comparison.c	\
			test/binary_primary/test_magnitude_comparison.c	\
			test/unary_primary/test_check_type.c			\
			test/unary_primary/test_string_len.c			\
			test/test_two_argc.c							\
			test/test_three_argc.c							\
			test/test_four_argc.c							\
			test/test_builtin.c

BUILTINS_SRCS = $(addprefix $(BUILTINS_PATH),$(BUILTINS))
SRCS += $(BUILTINS_SRCS)
