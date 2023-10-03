# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 09:55:46 by mde-sa--          #+#    #+#              #
#    Updated: 2023/10/03 11:32:05 by mde-sa--         ###   ########.fr        #
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

SRC		=	main.c arg_check.c thread_management.c

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
