# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 21:13:04 by crigonza          #+#    #+#              #
#    Updated: 2023/03/25 19:42:05 by crigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= gcc -lreadline -I/opt/homebrew/opt/readline/include
CFLAGS	= 
LIBFT	= ./libft

HEADERS = -I ./inc
LIBS	= $(LIBFT)/libft.a
SRCS 	= $(shell find ./src -iname "*.c")
OBJS	= ${SRCS:.c=.o}

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

%.0: &.C
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	$(MAKE)	-C $(LIBFT) clean

fclean:clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re:	clean all

.PHONY: all, clean, fclean, re, libft
