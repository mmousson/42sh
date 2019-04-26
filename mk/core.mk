# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    core.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 11:45:43 by mmousson          #+#    #+#              #
#    Updated: 2019/04/26 11:45:55 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CORE_PATH = ./src/core/
CORE =	main.c					\
		term_config.c

CORE_SRCS = $(addprefix $(CORE_PATH),$(CORE))
SRCS += $(CORE_SRCS)
