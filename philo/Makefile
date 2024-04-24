# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 09:55:46 by mde-sa--          #+#    #+#              #
#    Updated: 2024/04/24 16:30:50 by mde-sa--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=   philo

CC      = 	cc

CFLAGS   =  -Wall -Wextra -Werror -pthread -g #-fsanitize=thread

SRCDIR	=	src

INCDIR	=   includes

INCFLAGS =  -I $(INCDIR)

SRC		=	main.c arg_check.c arg_init.c mutexes_init.c manage_threads.c \
			routines.c fork_eat_think_sleep.c monitoring_printing_thread.c \
			printing_buffer.c end_conditions.c \
			mutex_utils_getter.c mutex_utils_setter.c time_utils.c \
			clean_data.c warning.c \
			extras/ft_atoi.c extras/ft_atol.c extras/ft_isdigit.c extras/ft_strlen.c

OBJS	= 	$(addprefix $(SRCDIR)/, $(SRC:.c=.o))

RM      = 	rm -rf


all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
