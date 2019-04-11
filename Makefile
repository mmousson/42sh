# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/04 00:08:26 by mmousson          #+#    #+#              #
#    Updated: 2019/04/11 20:00:47 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
LIBFT = libft
LIBS = -lft
LIBSFOLDERS = -L./$(LIBFT)
vpath %.c $(dir MAKEFILE_LIST)
CFLAGS = -g3 -Wall -Wextra -Werror -I./includes -I./includes/builtins -I./libft/includes
CPPFLAGS += -MMD -MP
OBJDIR = .o

NAME = 42sh

SRCS =		./src/core/main.c						\
			./src/builtins/fg.c						\
			./src/builtins/bg.c						\
			./src/builtins/jobs.c					\
			./src/job_control/initialize.c			\
			./src/job_control/child_process.c		\
			./src/job_control/parent_process.c		\
			./src/job_control/job_engine.c			\
			./src/job_control/foreground.c			\
			./src/job_control/background.c			\
			./src/job_control/mark_process_status.c	\
			./src/job_control/update_job_status.c	\
			./src/job_control/sig_table.c			\
			./src/job_control/sigchld_handler.c		\
			./src/job_control/utility.c

OBJS = $(subst .c,.o,$(subst ./src/,./$(OBJDIR)/,$(SRCS)))
DEPS = $(subst .c,.d,$(subst ./src/,./$(OBJDIR)/,$(SRCS)))

all: lib_rule $(NAME)

$(NAME): $(OBJS)
	@$(RM) tmp_log
	@$(RM) tmp_errors
	@if [ -e files_missing ]; then \
		printf "\033[1;31m\n[42SH COMPILATION FAILED]\033[0m\n"; \
	else \
		$(CC) $(OBJS) -o $(NAME) $(LIBSFOLDERS) $(LIBS); \
		printf "\033[1;36m\n[42SH COMPILATION SUCCESSFUL]\033[0m\n"; \
	fi;
	@$(RM) files_missing

$(OBJDIR):
	@$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@$(shell mkdir -p $(dir $@))
	@printf "%-40s" "Precompiling $(notdir $@)..."
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< 2> ./tmp_log || /usr/bin/touch ./tmp_errors
	@if [ -e tmp_errors ]; then \
		printf "\033[1;31m[KO]\n\033[0m" && /bin/cat 1>&2 ./tmp_log && touch files_missing; \
	elif test -s ./tmp_log; then \
		printf "   \033[1;33m[WARNING]\n\033[0m" && /bin/cat ./tmp_log; \
	else \
		printf "   \033[1;32m[OK]\n\033[0m"; \
	fi;

clean:
	@$(MAKE) -C $(LIBFT) clean --no-print-directory
	@$(RM) $(OBJS) $(DEPS)
	@printf "\033[1;33m[42SH OBJECT FILES CLEANED]\033[0m\n"

fclean:
	@$(MAKE) -C $(LIBFT) fclean --no-print-directory
	@$(RM) $(OBJS) $(DEPS)
	@printf "\033[1;33m[42SH OBJECT FILES CLEANED]\033[0m\n"
	@$(RM) $(NAME)
	@printf "\033[1;35m[42SH BINARY DELETED]\033[0m\n"

re: fclean all

fclean_nolib:
	@$(RM) $(OBJS) $(DEPS)
	@printf "\033[1;33m[42SH OBJECT FILES CLEANED]\033[0m\n"
	@$(RM) $(NAME)
	@printf "\033[1;35m[42SH BINARY DELETED]\033[0m\n"

re_nolib: fclean_nolib all

lib_rule:
	@$(MAKE) -C $(LIBFT) --no-print-directory

.NOTPARALLEL:
.PHONY: lib_rule all clean fclean re re_nolib fclean_nolib
-include $(DEPS)
