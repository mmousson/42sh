# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utility.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 12:03:51 by mmousson          #+#    #+#              #
#    Updated: 2019/04/26 12:05:06 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILITY_PATH = ./src/utility/

UTILITY =	add_internal_var.c			\
			alias_exists.c				\
			alias_init.c				\
			builtins_utility.c			\
			environ_aux_functions.c		\
			environ_utilities.c			\
			free_alias_list.c			\
			get_user_home.c				\
			hash_string.c				\
			internal_var_exists.c		\
			write_alias_list_to_file.c

UTILITY_SRCS = $(addprefix $(UTILITY_PATH),$(UTILITY))
SRCS += $(UTILITY_SRCS)
