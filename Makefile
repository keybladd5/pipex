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

NAME_BONUS	= pipex_bonus

SRCS =  src/pipex.c src/pipex_utils.c

SRCS_BONUS = src_bonus/pipex_bonus.c src_bonus/pipex_utils_bonus.c 

INCLUDES = inc/pipex.h

INCLUDES_BONUS = inc_bonus/pipex_bonus.h 

FLAGS = -Wall -Wextra -Werror -MMD -g

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

DEPS = $(SRCS:.c=.d)

DEPS_BONUS = $(SRCS_BONUS:.c=.d)

all: makelibft $(NAME)

CC = gcc

%.o:%.c Makefile libft/libft.a inc_bonus/pipex_bonus.h
	$(CC) $(FLAGS) -I ./ -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) libft/libft.a $(OBJS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(FLAGS) libft/libft.a $(OBJS_BONUS) -o $(NAME_BONUS)

makelibft: 
	$(MAKE) -C libft/

bonus: makelibft $(NAME_BONUS)

clean:
	rm -rf $(OBJS) $(DEPS)
	rm -rf $(OBJS_BONUS) $(DEPS_BONUS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

-include $(DEPS)
-include $(DEPS_BONUS)

.PHONY: all clean fclean re makelibft
