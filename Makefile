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


ifneq ($(shell uname), Linux)
READLINE_LIB_DIR_FLAG := -L$(shell brew --prefix readline)/lib
READLINE_INC_DIR_FLAG := -I$(shell brew --prefix readline)/include
endif

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS		= minishell.c srcs/ft_dquote.c \
				srcs/ft_free.c srcs/ft_get_input.c srcs/ft_perror.c \
				srcs/ft_utils_1.c srcs/ft_utils_2.c srcs/parsing/ft_check.c \
				srcs/parsing/ft_penv.c srcs/parsing/ft_parse.c srcs/parsing/ft_process.c \
				srcs/parsing/ft_quote.c srcs/parsing/ft_replace.c srcs/parsing/ft_search_env.c \
				srcs/parsing/ft_splitd.c srcs/built-in/ft_echo.c srcs/built-in/ft_env.c srcs/built-in/ft_export.c \
				srcs/built-in/ft_pwd.c srcs/built-in/ft_is_commad.c srcs/built-in/ft_exit.c srcs/built-in/ft_cd.c \
				srcs/built-in/ft_unset.c srcs/parsing/ft_parse_utils.c srcs/built-in/ft_export_utils.c \
				srcs/built-in/ft_remove_in.c srcs/ft_exec_cmd.c srcs/ft_exec_cmd_2.c srcs/ft_exec_cmd_3.c \
				srcs/ft_exec_utils.c srcs/ft_fork.c srcs/ft_fork_2.c srcs/ft_fork_3.c srcs/ft_free_exec.c \
				srcs/ft_built_switch.c srcs/ft_init_exec.c srcs/parsing/ft_penv_utils.c srcs/ft_signal.c
NAME		= minishell
OBJS_DIR	= objs/
PROJECT_H	= includes/minishell.h
OBJS		= $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
CC			= gcc
CC_FLAGS	= #-Wall -Werror -Wextra -fsanitize=address -g3 #-Wall -Werror -Wextra

$(OBJS_DIR)%.o : %.c $(PROJECT_H)
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs
	@mkdir -p $(OBJS_DIR)srcs/parsing
	@mkdir -p $(OBJS_DIR)srcs/built-in
	@mkdir -p $(OBJS_DIR)get_next_line
	@$(CC) $(READLINE_INC_DIR_FLAG) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD]${RST} '$<' $(END)"

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS) $(READLINE_LIB_DIR_FLAG) libft/libft.a ft_printf/libftprintf.a -lreadline 
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