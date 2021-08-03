# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rmeiboom <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/15 16:56:30 by rmeiboom      #+#    #+#                  #
#    Updated: 2021/07/08 14:15:05 by rmeiboom      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = clang
NAME = a.out
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
TESTER = tester
CHECKER = checker
LIBS = utils/libft/libft.a  utils/ft_printf/libftprintf.a
LIBFTDIR = utils/libft/
FT_PRINTFDIR = utils/ft_printf/
GNLDIR = utils/gnl/
ACTIONSDIR = srcs/actions/
UTILSDIR = utils/

OBJ = $(GNLDIR)get_next_line.o $(GNLDIR)get_next_line_utils.o\

TEST_OBJ = tests/test_main.o

CHECKER_OBJ = bonus/main.o

all: $(NAME)

$(NAME): $(OBJ) main.o
		make -C $(LIBFTDIR)
		make -C $(FT_PRINTFDIR)
		$(CC) $(CFLAGS) $(OBJ) $(LIBS) main.c -o $(NAME)

bonus: $(OBJ) $(CHECKER_OBJ)
		make -C $(LIBFTDIR)
		make -C $(FT_PRINTFDIR)
		$(CC) $(CFLAGS) $(OBJ) $(CHECKER_OBJ) $(LIBS) -o $(CHECKER)

run: $(NAME)
		./scripts/run.sh

run_tests: test
		./$(TESTER)

test: $(OBJ) $(TEST_OBJ)
	make -C $(LIBFTDIR)
	make -C $(FT_PRINTFDIR)
	$(CC) $(CFLAGS) $(OBJ) $(TEST_OBJ) $(LIBS) -o $(TESTER)

%.o: %.c
		$(CC) -c $(CFLAGS) -o $@ $<

clean:
		rm -f $(OBJ) $(TEST_OBJ) $(CHECKER_OBJ) norminette_result
		rm -f main.o
		make -C $(LIBFTDIR) fclean
		make -C $(FT_PRINTFDIR) fclean

fclean: clean
		rm -f $(NAME)
		rm -f $(TESTER)
		rm -f $(CHECKER)

re: fclean all

.PHONY: all clean fclean re bonus run_tests test checker run
