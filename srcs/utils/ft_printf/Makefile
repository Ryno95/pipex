# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rmeiboom <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/02 13:21:55 by rmeiboom      #+#    #+#                  #
#    Updated: 2021/01/16 11:48:29 by rmeiboom      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC=gcc

CFLAGS = -Wall -Werror -Wextra

NAME = libftprintf.a

HEADERS = ft_printf.h

OBJ = 	ft_printf.o\
		parse_and_write/handle_flags.o\
		parse_and_write/handle_type.o\
		parse_and_write/handle_str_and_chrs.o\
		parse_and_write/handle_ints.o\
		parse_and_write/handle_hexa_and_ptr.o\
		utils/ft_printf_utils.o\
		utils/ft_atoi.o\
		utils/ft_isdigit.o\
		utils/ft_strchr.o\
		utils/ft_strlen.o

all: $(NAME)

$(NAME): 	$(OBJ)
			ar rc $@ $^
			ranlib $@

%.o: 		%.c $(HEADERS)
			$(CC) -c $(CFLAGS) -o $@ $<

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
