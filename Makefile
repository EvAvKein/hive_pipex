# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:31:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/02/04 11:08:43 by ekeinan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT_DIR = libft_full
LIBFT_LIB = $(LIBFT_DIR)/libft_full.a

SRC_DIR = src
SRC_FILES = main.c \
			pipex.c \
			cmd.c \
			utils.c \
			perrs.c \
			here_doc.c

COMPILE_FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC_FILES:%.c=$(SRC_DIR)/%.o)

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) -s --no-print-directory

%.o: %.c
	cc $(COMPILE_FLAGS) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(OBJ)
	cc $(COMPILE_FLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	rm -rf $(NAME)

re: fclean all

neat: $(NAME) clean
	clear

.PHONY: all bonus clean fclean re