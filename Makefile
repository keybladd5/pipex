# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 11:07:51 by polmarti          #+#    #+#              #
#    Updated: 2024/01/16 11:07:53 by polmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS =  src/pipex.c src/pipex_utils.c 

INCLUDES = inc/pipex.h

FLAGS = -Wall -Wextra -Werror -MMD -fsanitize=address

OBJS = $(SRCS:.c=.o)

DEPS = $(SRCS:.c=.d)

all: makelibft $(NAME)

CC = gcc

%.o:%.c Makefile
	$(CC) $(FLAGS) -I ./ -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) libft/libft.a $(OBJS) -o $(NAME)

makelibft: 
	$(MAKE) -C libft/

clean:
	rm -rf $(OBJS) $(DEPS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re makelibft
