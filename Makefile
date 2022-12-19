# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/13 15:56:31 by kdoulyaz          #+#    #+#              #
#    Updated: 2022/10/02 21:11:34 by kdoulyaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/minishell.c src/signals.c src/lexer/lexer.c src/lexer/token.c src/lexer/lexer_utils.c src/parce/parce.c src/parce/qaout_utils.c\
		src/parce/expand.c src/parce/expand_utils.c src/parce/qaout.c src/parce/redirections_utils.c src/parce/free.c src/here_doc/utils.c\
		src/parce/args.c src/parce/init_struct.c src/parce/pipe.c src/parce/redirections.c src/exec/exec.c src/exec/norm.c \
		src/builtins/builtins.c src/builtins/pwd.c src/builtins/cd.c src/exec/exec_utils.c src/exec/utils.c src/builtins/echo.c \
		src/builtins/exit.c src/parce/envp.c src/errors_handle/handle_errors.c src/builtins/env.c src/builtins/unset.c\
		src/builtins/export.c src/parce/utils.c src/builtins/exp_utils1.c src/builtins/unset_utils.c src/here_doc/her_doc.c\
		src/errors_handle/handle_errors_utils.c src/errors_handle/handle_errors_utils1.c src/parce/redirection_utils1.c\

CC = @gcc -g -lreadline #-fsanitize=address

CFLAGS = -Wall -Wextra -Werror
# for oussama
# LFLAGS = -L ~/Desktop/brew/opt/readline/lib

# IFLAGS = -I ~/Desktop/brew/opt/readline/include
# for khalid 
LFLAGS = -L ~/.brew/opt/readline/lib

IFLAGS = -I ~/.brew/opt/readline/include

LIBFT = libft/libft.a

RM = @rm -f

all:		$(NAME)

$(NAME):
			@cd libft && make && make bonus && cd ..
			@stty -echoctl
			$(CC) $(CFLAGS) $(LIBFT) $(SRC) -lreadline $(LFLAGS) $(IFLAGS) -o $(NAME)
			@echo "\033[0;32m®minishell CREATED 🐲\033[0m"

clean:
			@cd libft && make clean && cd ..

fclean: 	
			@cd libft && make fclean && cd ..
			$(RM) $(NAME)
			@echo "\033[0;31mminishell DELETED 🗑"

re:			fclean all
