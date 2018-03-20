# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: droly <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/27 15:32:49 by droly             #+#    #+#              #
#    Updated: 2018/03/20 17:13:53 by droly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nm

SRC = nm.c \
	  nm_64.c \
	  nm_64_reverse.c \
	  print_output.c \
	  error.c \
	  nm_32.c \
	  nm_32_reverse.c \
	  print_output32.c \
	  print_output32_reverse.c \
	  reverse.c \
	  nm+.c

OBJ = $(SRC:.c=.o)

LIB = ../libft/libft.a

FLAGS = -Wall -Wextra -Werror

all: makelibft $(NAME)

$(NAME): $(OBJ)
	@echo "✅  \\033[1;35;mStart compilation (nm)...\033[0m"
	@clang $(FLAGS) -c $(SRC)
	@clang $(LIB) $(OBJ) -o $(NAME)
	@echo "✅  \\033[1;32;mCompilation success (nm) !\033[0m"

makelibft:
	@echo "✅  \\033[1;36;mLinking libft (nm)...\033[0m"
	@make -C ../libft/

clean:
	@echo "✅  \\033[1;31;mCleaning *.o (nm)...\033[0m"
	@make clean -C ../libft/
	@rm -f $(OBJ)

fclean: clean
	@echo "✅  \\033[1;31;mDeleting all (nm)..\033[0m"
	@make fclean -C ../libft/
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
