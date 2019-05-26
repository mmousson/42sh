# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/04 00:08:26 by mmousson          #+#    #+#              #
#    Updated: 2019/05/25 13:54:15 by oboutrol         ###   ########.fr        #
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

CC = gcc
LIBFT = libft
LIBS = -lft
LIBSFOLDERS = -L./$(LIBFT)
vpath %.c $(dir MAKEFILE_LIST)
CFLAGS = -g3 -Wall -Wextra -Werror -I./includes -I./includes/builtins -I./libft/includes -Wno-deprecated
CPPFLAGS += -MMD -MP
OBJDIR = .o
UNAME = $(shell uname)
ifeq ($(UNAME), Linux)
	DECODE64_FLAG = -d
else
	DECODE64_FLAG = -d
endif
ALIAS_LIST = "bHM9bHMgLUcKbD1scyAtbGFoCmxsPWxzIC1saApncmVwICAtLWNvbG9yPWF1dG8gLS1leGNsdWRlLWRpcj17LmJ6cixDVlMsLmdpdCwuaGcsLnN2bn0KLT1jZCAtCi4uLj0uLi8uLgouLi4uPS4uLy4uLy4uCi4uLi4uPS4uLy4uLy4uLy4uCi4uLi4uLj0uLi8uLi8uLi8uLi8uLgoxPWNkIC0KMj1jZCAtMgozPWNkIC0zCjQ9Y2QgLTQKNT1jZCAtNQo2PWNkIC02Cjc9Y2QgLTcKOD1jZCAtOAo5PWNkIC05CmdjYj1naXQgY2hlY2tvdXQgLWIKZ2NkPWdpdCBjaGVja291dCBkZXZlbG9wCmdjZj1nY2MgLVdhbGwgLVdleHRyYSAtV2Vycm9yCmdjbD1naXQgY2xvbmUgLS1yZWN1cnNlLXN1Ym1vZHVsZXMKZ2NsZWFuPWdpdCBjbGVhbiAtZmQKZ2NtPWdpdCBjaGVja291dCBtYXN0ZXIKZ2Ntc2c9Z2l0IGNvbW1pdCAtbQo="

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
		$(CC) $(OBJS) -o $(NAME) $(LIBSFOLDERS) $(LIBS) -ltermcap; \
		printf "\033[1;36m\n[42SH COMPILATION SUCCESSFUL]\033[0m\n"; \
	fi;
	@echo $(ALIAS_LIST) | base64 $(DECODE64_FLAG) > ~/.42sh_aliases
	@$(RM) files_missing

$(OBJDIR):
	@$(shell mkdir -p $(OBJDIR))

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@$(shell mkdir -p $(dir $@))
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
