# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: droly <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/27 15:32:49 by droly             #+#    #+#              #
#    Updated: 2018/03/26 11:54:44 by droly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_otool

SRC = otool.c \
	  otool_64.c \
	  otool_64_reverse.c \
	  print_output.c \
	  error.c \
	  otool_32.c \
	  otool_32_reverse.c \
	  print_output32.c \
	  print_output32_reverse.c \
	  reverse.c \
	  otool2.c \
	  addotool.c

OBJ = $(SRC:.c=.o)

LIB = ../libft/libft.a

FLAGS = -Wall -Wextra -Werror

all: makelibft $(NAME)

$(NAME): $(OBJ)
	@echo "✅  \\033[1;35;mStart compilation (otool)...\033[0m"
	@clang $(FLAGS) -c $(SRC)
	@clang $(LIB) $(OBJ) -o $(NAME)
	@echo "✅  \\033[1;32;mCompilation success (otool) !\033[0m"

makelibft:
	@echo "✅  \\033[1;36;mLinking libft (otool)...\033[0m"
	@make -C ../libft/

clean:
	@echo "✅  \\033[1;31;mCleaning *.o (otool)...\033[0m"
	@make clean -C ../libft/
	@rm -f $(OBJ)

fclean: clean
	@echo "✅  \\033[1;31;mDeleting all (otool)..\033[0m"
	@make fclean -C ../libft/
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
