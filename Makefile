# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_casa                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 21:13:04 by crigonza          #+#    #+#              #
#    Updated: 2023/03/29 17:17:37 by crigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= gcc
CFLAGS	=
L_FLAGS = -lreadline
/* LDFLAGS= -L/opt/homebrew/opt/readline/lib */
/* CPPFLAGS= -I/opt/homebrew/opt/readline/include*/
LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include 
LIBFT	= ./libft

HEADERS = -I ./inc
LIBS	= $(LIBFT)/libft.a
SRCS 	= $(shell find ./src -iname "*.c")
OBJS	= ${SRCS:.c=.o}

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

%.o: &.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $< $(HEADERS)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) $(CPPFLAGS) $(LIBS) $(HEADERS) -o $(NAME) $(L_FLAGS)

clean:
	@rm -f $(OBJS)
	$(MAKE)	-C $(LIBFT) clean

fclean:clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re:	clean all

.PHONY: all, clean, fclean, re, libft