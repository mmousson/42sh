# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utility.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 12:03:51 by mmousson          #+#    #+#              #
#    Updated: 2019/04/27 01:25:36 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILITY_PATH = ./src/utility/

UTILITY =	utility_add_internal_var.c			\
			utility_alias_exists.c				\
			utility_alias_init.c				\
			utility_builtins_utility.c			\
			utility_environ_aux_functions.c		\
			utility_environ_utilities.c			\
			utility_free_alias_list.c			\
			utility_get_user_home.c				\
			utility_hash_string.c				\
			utility_internal_var_exists.c		\
			utility_write_alias_list_to_file.c

UTILITY_SRCS = $(addprefix $(UTILITY_PATH),$(UTILITY))
SRCS += $(UTILITY_SRCS)
