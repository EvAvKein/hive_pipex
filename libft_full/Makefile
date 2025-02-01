# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:31:47 by ekeinan           #+#    #+#              #
#    Updated: 2024/12/20 17:59:44 by ekeinan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_full.a
LIB = libft.a

SRC = ft_printf.c \
	  increase_print_count.c \
	  print_chars.c \
	  print_int.c \
	  print_ptr.c \
	  print_hex.c \
	  get_next_line_bonus.c \
      get_next_line_utils_bonus.c

OBJ = $(SRC:.c=.o)

COMPILE_FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	cc $(COMPILE_FLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIB)
	@mv $(LIB) $(NAME)
	ar -rcs $(NAME) $(OBJ)

$(LIB):
	@make bonus -C ./libft
	cp ./libft/$(LIB) ./

clean:
	@cd libft && make $@
	rm -f $(OBJ)

fclean: clean
	@cd libft && make $@
	rm -f $(NAME)

re: fclean all
	@cd libft && make $@

.PHONY: all bonus clean fclean re
