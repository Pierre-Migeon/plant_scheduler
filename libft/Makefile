# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/10 16:09:15 by pmigeon           #+#    #+#              #
#    Updated: 2018/11/25 21:41:53 by pmigeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = *.c
HEADER = ./
LIBNAME = libft.a
COMPILER = gcc
FLAGS = -Wall -Werror -Wextra -c
OFILE = $(SOURCES:.c=.o)
NAME = libft.a

all: $(NAME)

$(NAME):
	@echo "compiling libft"
	@$(COMPILER) $(FLAGS) $(SOURCES) -I $(HEADER)
	@ar rc $(LIBNAME) $(OFILE)
	@ranlib $(LIBNAME)

clean:
	@echo "Cleaning *.o from libft"
	@/bin/rm -f $(OFILE)

fclean: clean
	@echo "Cleaning everything from libft"
	@/bin/rm -f $(LIBNAME)

re: fclean all
