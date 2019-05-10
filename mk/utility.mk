# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utility.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 12:03:51 by mmousson          #+#    #+#              #
#    Updated: 2019/05/08 09:17:30 by roliveir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILITY_PATH = ./src/utility/

UTILITY =	add_internal_var.c					\
			alias_exists.c						\
			alias_init.c						\
			builtins_utility.c					\
			environ_aux_functions.c				\
			environ_utilities.c					\
			free_alias_list.c					\
			get_user_home.c						\
			utility_get_effective_username.c	\
			hash_string.c						\
			internal_var_exists.c				\
			write_alias_list_to_file.c

UTILITY_SRCS = $(addprefix $(UTILITY_PATH),$(UTILITY))
SRCS += $(UTILITY_SRCS)
