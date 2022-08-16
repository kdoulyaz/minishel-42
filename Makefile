# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/13 15:56:31 by kdoulyaz          #+#    #+#              #
#    Updated: 2022/08/16 05:02:17 by kdoulyaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/minishell.c src/lexer/lexer.c src/lexer/token.c src/lexer/lexer_utils.c src/parce/parce.c\
		src/parce/args.c src/parce/init_struct.c src/parce/pipe.c src/parce/redirections.c src/exec/exec.c \
		src/builtins/builtins.c src/builtins/pwd.c

CC = @gcc -g -lreadline  #-fsanitize=address

CFLAGS = -Wall -Wextra -Werror

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

t:
			@./$(NAME)
clean:
			@cd libft && make clean && cd ..

fclean: 	
			@cd libft && make fclean && cd ..
			$(RM) $(NAME)
			@echo "\033[0;31mminishell DELETED 🗑"

re:			fclean all 