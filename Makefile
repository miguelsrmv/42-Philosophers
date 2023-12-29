# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 09:55:46 by mde-sa--          #+#    #+#              #
#    Updated: 2023/12/29 19:08:27 by mde-sa--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=   philosophers

CC      = 	cc

CFLAGS   =  -Wall -Wextra -Werror -g -pthread

SRCDIR	=	src

INCDIR	=   includes

LIBFTDIR =  src/libft

LIBS	=   -L$(LIBFTDIR) -lft

INCFLAGS =  -I $(INCDIR) -I $(LIBFTDIR)

SRC		=	main.c arg_check.c thread_management.c time_functions.c routine.c \
			eat_think_sleep.c update_mutex.c update_forks.c print_message.c \
			buffered_output.c clear_memory.c helper_functions.c

OBJS	= 	$(addprefix $(SRCDIR)/, $(SRC:.c=.o))

RM      = 	rm -rf


all: libft $(NAME)

$(NAME): $(OBJS) 
	@ $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) 

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
	@ $(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

libft:
	@ cd $(LIBFTDIR) && make -s && make -s clean

clean:
	@ $(MAKE) -sC $(LIBFTDIR) clean
	@ $(RM) $(OBJS)

fclean: clean
	@ $(MAKE) -sC $(LIBFTDIR) fclean
	@ $(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft

test:
	./philosophers 4 10 10 10