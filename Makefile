# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: droly <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/27 15:32:49 by droly             #+#    #+#              #
#    Updated: 2018/03/12 10:16:55 by droly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME = nm-otool

#SRC = otool.c \
#	  error.c

#OBJ = $(SRC:.c=.o)

#LIB = ../libft/libft.a

#FLAGS = -Wall -Wextra -Werror

all: makenm-otool

#$(NAME): $(OBJ)
#	@echo "✅  \\033[1;35;mStart compilation...\033[0m"
#	@clang $(FLAGS) -c $(SRC)
#	@clang $(LIB) $(OBJ) -o $(NAME)
#	@echo "✅  \\033[1;32;mCompilation success !\033[0m"

makenm-otool:
	@echo "✅  \\033[1;36;mcompiling nm...\033[0m"
	@make -C ./nm/
	@echo "✅  \\033[1;36;mcompiling otool...\033[0m"
	@make -C ./otool/

clean:
	@echo "✅  \\033[1;31;mCleaning *.o...\033[0m"
	@make clean -C ./otool/
	@make clean -C ./nm/

fclean: clean
	@echo "✅  \\033[1;31;mDeleting all..\033[0m"
	@make fclean -C ./otool/
	@make fclean -C ./nm/

re: fclean all

.PHONY: all clean fclean re
