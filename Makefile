# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rmeiboom <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/15 16:56:30 by rmeiboom      #+#    #+#                  #
#    Updated: 2021/08/09 13:07:56 by rmeiboom      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = pipex
CFLAGS = -Wall -Werror -Wextra
TESTER = tester
CHECKER = checker
LIBS = srcs/utils/libft/libft.a  srcs/utils/ft_printf/libftprintf.a
LIBFTDIR = srcs/utils/libft/
FT_PRINTFDIR = srcs/utils/ft_printf/
GNLDIR = srcs/utils/gnl/
UTILSDIR = srcs/utils/

OBJ = $(GNLDIR)get_next_line.o $(GNLDIR)get_next_line_utils.o\
		srcs/pipex.o srcs/pipex_utils.o srcs/handle_errors.o\
		srcs/get_exe_path.o

TEST_OBJ = tests/main.o tests/test_args.o tests/test_get_path.o

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
