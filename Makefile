# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:15:12 by tnard             #+#    #+#              #
#    Updated: 2021/12/10 11:10:35 by tnard            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS		= minishell.c srcs/execute_cmd.c srcs/ft_dquote.c \
				srcs/ft_free.c srcs/ft_get_input.c srcs/ft_perror.c \
				srcs/ft_utils_1.c srcs/ft_utils_2.c srcs/parsing/ft_check.c \
				srcs/parsing/ft_env.c srcs/parsing/ft_parse.c srcs/parsing/ft_process.c \
				srcs/parsing/ft_quote.c srcs/parsing/ft_replace.c srcs/parsing/ft_search_env.c \
				srcs/parsing/ft_splitd.c
NAME		= minishell
OBJS_DIR	= objs/
PROJECT_H	= includes/minishell.h
OBJS		= $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
CC			= gcc
CC_FLAGS	= #-Wall -Werror -Wextra #-fsanitize=address -g3

$(OBJS_DIR)%.o : %.c $(PROJECT_H)
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs
	@mkdir -p $(OBJS_DIR)temp
	@mkdir -p $(OBJS_DIR)srcs/parsing
	@mkdir -p $(OBJS_DIR)get_next_line
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD]${RST} '$<' $(END)"

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS) libft/libft.a ft_printf/libftprintf.a -lreadline 
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

all: $(NAME)

maker:
	@make -C libft
	@make -C ft_printf

clean:
	@make clean -C libft
	@make clean -C ft_printf
	@rm -rf $(OBJS_DIR)
	@printf "\033[2K\r${GRN}[CLEAN]${RST} done$(END)"

fclean: clean
	@make fclean -C libft
	@make fclean -C ft_printf
	@rm -f $(NAME)
	@printf "\033[2K\r${GRN}[FCLEAN]${RST} done$(END)"

re: fclean all

.PHONY:		all clean fclean re