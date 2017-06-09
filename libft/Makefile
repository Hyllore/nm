# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: droly <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 17:07:51 by droly             #+#    #+#              #
#    Updated: 2017/06/08 17:07:08 by droly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memset.c				\
      ft_bzero.c				\
      ft_memcpy.c				\
      ft_memccpy.c				\
      ft_memmove.c				\
      ft_memchr.c				\
      ft_memcmp.c				\
      ft_strlen.c				\
      ft_strdup.c				\
      ft_strcpy.c				\
      ft_strncpy.c				\
      ft_strcat.c				\
      ft_strncat.c				\
      ft_strlcat.c				\
      ft_strchr.c				\
      ft_strrchr.c				\
      ft_strstr.c				\
      ft_strnstr.c				\
      ft_strcmp.c				\
      ft_strncmp.c				\
      ft_atoi.c					\
      ft_isalpha.c				\
      ft_isdigit.c				\
      ft_isalnum.c				\
      ft_isascii.c				\
      ft_isprint.c				\
      ft_toupper.c				\
      ft_tolower.c				\
      ft_memalloc.c				\
      ft_memdel.c				\
      ft_strnew.c				\
      ft_strdel.c				\
      ft_strclr.c				\
      ft_striter.c				\
      ft_striteri.c				\
      ft_strmap.c				\
      ft_strmapi.c				\
      ft_strequ.c				\
      ft_strnequ.c				\
      ft_strsub.c				\
      ft_strjoin.c				\
      ft_strtrim.c				\
      ft_itoa.c					\
      ft_putchar.c				\
      ft_putstr.c				\
      ft_strsplit.c				\
      ft_putendl.c				\
      ft_putchar_fd.c			\
      ft_putstr_fd.c			\
      ft_putendl_fd.c			\
      ft_putnbr.c				\
      ft_putnbr_fd.c			\
      ft_lstnew.c				\
      ft_lstdelone.c			\
      ft_lstdel.c				\
      ft_lstadd.c				\
      ft_lstmap.c				\
      ft_lstiter.c				\
      ft_utoa.c					\
      ft_itoa_base.c			\
      ft_putnbr_u.c				\
      ft_power.c				\
      ft_putwchar.c				\
      ft_putwstr.c				\
      ft_itoa_base_ull.c		\
      ft_utoi.c					\
      get_next_line.c			\
      ft_printf/apply_types.c	\
      ft_printf/apply_types2.c	\
      ft_printf/check_types.c	\
      ft_printf/ft_printf.c		\
      ft_printf/take_type.c		\
      ft_printf/len_modif.c		\
      ft_printf/len_modif_d_i.c	\
      ft_printf/len_modif_o_u.c	\
      ft_printf/unicode.c		\
      ft_printf/add_bonus.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

.PHONY: clean fclean re

all: $(NAME)

$(NAME) :
	@clang $(FLAGS) -c $(SRC)
	@mv apply_types.o apply_types2.o check_types.o ft_printf.o ft_printf/
	@mv take_type.o len_modif.o len_modif_d_i.o len_modif_o_u.o ft_printf/
	@mv unicode.o add_bonus.o ft_printf/
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
