# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:31:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/02/22 23:38:31 by ekeinan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
BONUS_NAME := pipex_bonus

LIBFT_DIR := libft_full
LIBFT_LIB := $(LIBFT_DIR)/libft_full.a

SRC_DIR := src
SRC_MAND_FILES := main_mandatory.c \
				  cmd.c \
				  binaries.c \
				  exit.c \
				  utils.c \
				  perrs.c

SRC_BONUS_FILES := main_bonus.c \
				   pipex_bonus.c \
				   cmd.c \
				   binaries.c \
				   exit.c \
				   utils.c \
				   perrs.c

INCLUDE_DIR := include
INCLUDE_MAND := pipex.h \
				perrs.h
INCLUDE_BONUS := pipex_bonus.h \
				 perrs.h

COMPILE_FLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR)

OBJ_MAND := $(SRC_MAND_FILES:%.c=$(SRC_DIR)/%.o)
OBJ_BONUS := $(SRC_BONUS_FILES:%.c=$(SRC_DIR)/%.o)
HEADERS_MAND := $(INCLUDE_MAND:%=$(INCLUDE_DIR)/%)
HEADERS_BONUS := $(INCLUDE_BONUS:%=$(INCLUDE_DIR)/%)

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) -s --no-print-directory

%.o: %.c
	cc $(COMPILE_FLAGS) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(OBJ_MAND) $(HEADERS_MAND)
	cc $(COMPILE_FLAGS) $(OBJ_MAND) $(LIBFT_LIB) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT_LIB) $(OBJ_BONUS) $(HEADERS_BONUS)
	cc $(COMPILE_FLAGS) $(OBJ_BONUS) $(LIBFT_LIB) -o $(BONUS_NAME)

clean:
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(OBJ_MAND) $(OBJ_BONUS)

fclean: clean
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

neat: $(NAME) clean
	clear

.PHONY: all bonus clean fclean re
