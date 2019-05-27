# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utility.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 12:03:51 by mmousson          #+#    #+#              #
#    Updated: 2019/05/25 10:46:12 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILITY_PATH = ./src/utility/

UTILITY =	utility_add_internal_var.c			\
			utility_set_var.c					\
			utility_get_var.c					\
			utility_get_param.c					\
			utility_delete_var.c				\
			utility_alias_exists.c				\
			utility_alias_init.c				\
			utility_builtins_utility.c			\
			utility_environ_aux_functions.c		\
			utility_environ_utilities.c			\
			utility_file_exists.c				\
			utility_free_lists.c				\
			utility_generate_tmp_filename.c		\
			utility_get_user_home.c				\
			utility_hash_string.c				\
			utility_internal_var_exists.c		\
			utility_write_alias_list_to_file.c	\
			glob/check_matching_files.c			\
			glob/get_files.c					\
			glob/glob.c							\
			glob/lexer/lexerdel.c				\
			glob/lexer/tokenize.c				\
			glob/match_files.c					\
			glob/pattern_matching.c				\
			glob/range.c						\
			glob/tools/boolean.c				\
			glob/tools/expansion_quotes.c		\
			glob/tools/get_path_depth.c			\
			glob/tools/globlextok.c				\
			glob/tools/slice_path.c				\
			glob/tools/walk_quotes.c			\
			glob/tools/walk_word.c

UTILITY_SRCS = $(addprefix $(UTILITY_PATH),$(UTILITY))
SRCS += $(UTILITY_SRCS)
