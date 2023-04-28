# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 11:29:18 by aoropeza          #+#    #+#              #
#    Updated: 2022/11/02 11:29:20 by aoropeza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
SRCDIR	= src
OBJDIR	= obj
LIBFT	= libft

#INC	= -I ./inc -I $(LIBFT)/inc
#LFLAGS	= -L$(LIBFT) -lft -lreadline
INC		= -I ./inc -I $(LIBFT)/inc -I/Users/$(USER)/.brew/opt/readline/include
LFLAGS	= -L$(LIBFT) -lft -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
SRC		:= $(wildcard $(SRCDIR)/*/*.c)
OBJS	:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -rf

BOLD	= \033[1m
RED		= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

all: lib $(NAME)

lib:
	@$(MAKE) -C $(LIBFT)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) $(INC) -o $(NAME) $(LFLAGS) &&\
	printf "$(GREEN)$(BOLD)Here, your minishell\n$(RESET)"

obj/%.o : src/%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC) && printf "$(WHITE)$(BOLD)\rCompiling: \
	$(CYAN)$(notdir $@)$(GREEN)\r\e[35C[OK]\n$(RESET)"

clean:
	@$(RM) $(OBJDIR) && printf "$(GREEN)$(BOLD)All objects cleaned! :)\n$(RESET)"
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@$(RM) $(NAME) && printf "$(YELLOW)$(BOLD)$(NAME) $(GREEN)file cleaned! :)\
	\n$(RESET)"
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all bonus clean fclean re

