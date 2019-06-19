# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/04 00:08:26 by mmousson          #+#    #+#              #
#    Updated: 2019/06/18 12:46:02 by mmousson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include mk/builtins.mk
include mk/core.mk
include mk/job_control.mk
include mk/lexer.mk
include mk/parser.mk
include mk/exec.mk
include mk/expand.mk
include mk/line_edition.mk
include mk/utility.mk
include mk/history.mk
include mk/option.mk

CC = gcc
LIBFT = libft
LIBS = -lft
LIBSFOLDERS = -L./$(LIBFT)
vpath %.c $(dir MAKEFILE_LIST)
CFLAGS = -g3 -Wall -Wextra -Werror -I./includes -I./includes/builtins -I./libft/includes
CPPFLAGS += -MMD -MP
OBJDIR = .o
UNAME = $(shell uname)
ifeq ($(UNAME), Linux)
	DECODE64_FLAG = -d
else
	DECODE64_FLAG = -D
endif
ALIAS_LIST = "Z2Ntc2c9Z2l0IGNvbW1pdCAtbQpnY209Z2l0IGNoZWNrb3V0IG1hc3RlcgpnY2xlYW49Z2l0IGNsZWFuIC1mZApnY2w9Z2l0IGNsb25lIC0tcmVjdXJzZS1zdWJtb2R1bGVzCmdjZj1nY2MgLVdhbGwgLVdleHRyYSAtV2Vycm9yCmdjZD1naXQgY2hlY2tvdXQgZGV2ZWxvcApnY2I9Z2l0IGNoZWNrb3V0IC1iCi4uLi4uLj0uLi8uLi8uLi8uLi8uLgouLi4uLj0uLi8uLi8uLi8uLgouLi4uPS4uLy4uLy4uCi4uLj0uLi8uLgotPWNkIC0KZ3JlcCAgLS1jb2xvcj1hdXRvIC0tZXhjbHVkZS1kaXI9ey5ienIsQ1ZTLC5naXQsLmhnLC5zdm59CmxsPWxzIC1saApsPWxzIC1sYWgKbHM9bHMgLUcK"
NAME = 42sh

OBJS = $(subst .c,.o,$(subst ./src/,./$(OBJDIR)/,$(SRCS)))
DEPS = $(subst .c,.d,$(subst ./src/,./$(OBJDIR)/,$(SRCS)))

all: lib_rule $(NAME)

$(NAME): $(OBJS)
	@$(RM) tmp_log
	@$(RM) tmp_errors
	@if [ -e files_missing ]; then \
		printf "\033[1;31m\n[42SH COMPILATION FAILED]\033[0m\n"; \
	else \
		if [ -e /tmp/.42sh_makefile_link ]; then \
			$(CC) $(OBJS) -o $(NAME) $(LIBSFOLDERS) $(LIBS) -ltermcap; \
			printf "\033[1;36m\n[42SH COMPILATION SUCCESSFUL]\033[0m\n"; \
		fi;\
	fi;
	@echo $(ALIAS_LIST) | base64 $(DECODE64_FLAG) > ~/.42sh_aliases
	@$(RM) files_missing
	@$(RM) /tmp/.42sh_makefile_link

$(OBJDIR):
	@$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@$(shell mkdir -p $(dir $@))
	@$(shell touch /tmp/.42sh_makefile_link)
	@printf "%-50s" "Precompiling $(notdir $@)..."
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< 2> ./tmp_log || /usr/bin/touch ./tmp_errors
	@if [ -e tmp_errors ]; then \
		printf "\033[1;31m[KO]\n\033[0m" && /bin/cat 1>&2 ./tmp_log && touch files_missing; \
	elif test -s ./tmp_log; then \
		printf "\033[1;33m[WARNING]\n\033[0m" && /bin/cat ./tmp_log; \
	else \
		printf "\033[1;32m[OK]\n\033[0m"; \
	fi;
	@$(RM) ./tmp_errors

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
