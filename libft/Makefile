# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/07 00:53:31 by mmousson          #+#    #+#              #
#    Updated: 2019/03/11 19:36:28 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libft.a
HEADER = libft.h
vpath %.c %(dir MAKEFILE_LIST)
OBJDIR = .o
CFLAGS = -Wall -Wextra -Werror -I./includes
CPPFLAGS += -MMD -MP

SRC =	ft_memset.c				\
		ft_bzero.c				\
		ft_memcpy.c				\
		ft_memccpy.c			\
		ft_strlen.c				\
		ft_memchr.c				\
		ft_memcmp.c				\
		ft_memmove.c			\
		ft_strdup.c				\
		ft_strcpy.c				\
		ft_strncpy.c			\
		ft_strcat.c				\
		ft_strncat.c			\
		ft_strlcat.c			\
		ft_strchr.c				\
		ft_strrchr.c			\
		ft_strstr.c				\
		ft_strrstr.c			\
		ft_strnstr.c			\
		ft_strcmp.c				\
		ft_strncmp.c			\
		ft_atoi.c				\
		ft_atol.c				\
		ft_isalpha.c			\
		ft_isdigit.c			\
		ft_isxdigit.c			\
		ft_isalnum.c			\
		ft_isascii.c			\
		ft_isprint.c			\
		ft_putchar.c			\
		ft_toupper.c			\
		ft_tolower.c			\
		ft_putstr.c				\
		ft_putendl.c			\
		ft_putnbr.c				\
		ft_memalloc.c			\
		ft_memdel.c				\
		ft_strnew.c				\
		ft_strdel.c				\
		ft_strclr.c				\
		ft_striter.c			\
		ft_striteri.c			\
		ft_strmap.c				\
		ft_strmapi.c			\
		ft_strequ.c				\
		ft_strnequ.c			\
		ft_strsub.c				\
		ft_strjoin.c			\
		ft_strtrim.c			\
		ft_strsplit.c			\
		ft_itoa.c				\
		ft_putchar_fd.c			\
		ft_putstr_fd.c			\
		ft_putendl_fd.c			\
		ft_putnbr_fd.c			\
		ft_lstdepth.c			\
		ft_lstnew.c				\
		ft_lstdelone.c			\
		ft_lstdel.c				\
		ft_lstadd.c				\
		ft_lstiter.c			\
		ft_lstmap.c				\
		ft_lstpush.c			\
		ft_putllong.c			\
		ft_min.c				\
		ft_dmin.c				\
		ft_max.c				\
		ft_dmax.c				\
		ft_abs.c				\
		ft_clamp.c				\
		ft_strdivide_two.c		\
		ft_strendswith.c		\
		ft_strremove_at.c		\
		ft_fabs.c				\
		get_next_line.c

OBJ = $(subst .c,.o,$(addprefix ./$(OBJDIR)/,$(SRC)))
DEPS = $(subst .c,.d,$(addprefix ./$(OBJDIR)/,$(SRC)))

all: $(NAME)

$(OBJDIR):
	@$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@$(shell mkdir -p $(dir $@))
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\033[1;32m[LIBFT READY]\033[0m\n"

clean:
	@$(RM) $(OBJ) $(DEPS)
	@printf "\033[1;33m[LIBFT CLEANED]\033[0m\n"

fclean:
	@$(RM) $(OBJ) $(DEPS)
	@printf "\033[1;33m[LIBFT CLEANED]\033[0m\n"
	@$(RM) $(NAME)
	@printf "\033[1;35m[LIBFT LIBRARY DELETED]\033[0m\n"

re: fclean all

.NOTPARALLEL:
.PHONY: all clean fclean re libft
-include $(DEPS)