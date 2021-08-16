# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rmeiboom <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/15 16:56:30 by rmeiboom      #+#    #+#                  #
#    Updated: 2021/08/16 14:46:01 by rmeiboom      ########   odam.nl          #
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

MAIN_MAIN = srcs/main.o

OBJ = $(GNLDIR)get_next_line.o $(GNLDIR)get_next_line_utils.o\
		srcs/pipex.o srcs/pipex_utils.o srcs/handle_errors.o\
		srcs/get_exe_path.o

TEST_OBJ = tests/test_args.o tests/test_get_path.o

BONUS_OBJ = srcs/bonus/main.o srcs/bonus/bonus_utils.o

ifdef WITH_BONUS
O_FILES = $(BONUS_OBJ) $(OBJ)
else
O_FILES = $(OBJ) $(MAIN_MAIN)
endif

all: $(NAME)

$(NAME): $(O_FILES)
		make -C $(LIBFTDIR)
		make -C $(FT_PRINTFDIR)
		$(CC) $(CFLAGS) $(O_FILES) $(LIBS) -o $(NAME)

bonus: 
		$(MAKE) WITH_BONUS=1 all

run: $(NAME)
		./scripts/run.sh

run_tests: test
		./$(TESTER)

test: $(O_FILES) $(TEST_OBJ)
	make -C $(LIBFTDIR)
	make -C $(FT_PRINTFDIR)
	$(CC) $(CFLAGS) $(O_FILES) $(TEST_OBJ) $(LIBS) -o $(TESTER)

%.o: %.c
		$(CC) -c $(CFLAGS) -o $@ $<

clean:
		rm -f $(O_FILES) $(TEST_OBJ) $(CHECKER_OBJ) norminette_result
		rm -f main.o
		rm -f $(BONUS_OBJ)
		make -C $(LIBFTDIR) fclean
		make -C $(FT_PRINTFDIR) fclean

fclean: clean
		rm -f $(NAME)
		rm -f $(TESTER)
		rm -f $(CHECKER)

re: fclean all

.PHONY: all clean fclean re bonus run_tests test checker run
