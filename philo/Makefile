# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 09:55:46 by mde-sa--          #+#    #+#              #
#    Updated: 2024/03/31 18:13:05 by mde-sa--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=   philo

CC      = 	cc

CFLAGS   =  -Wall -Wextra -Werror -pthread -g

SRCDIR	=	src

INCDIR	=   includes

LIBFTDIR =  src/libft

LIBS	=   -L$(LIBFTDIR) -lft

INCFLAGS =  -I $(INCDIR) -I $(LIBFTDIR)

SRC		=	main.c arg_check.c arg_init.c clean_data.c manage_threads.c helpers.c \
			routines.c

OBJS	= 	$(addprefix $(SRCDIR)/, $(SRC:.c=.o))

RM      = 	rm -rf


all: libft $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) 

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

libft:
	@ cd $(LIBFTDIR) && make -s

clean:
	$(MAKE) -sC $(LIBFTDIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -sC $(LIBFTDIR) fclean
	$(RM) $(NAME)

re: fclean all

test:
	valgrind -q --leak-check=full --show-leak-kinds=all ./philo 5 100 100 100

.PHONY: all clean fclean re libft
