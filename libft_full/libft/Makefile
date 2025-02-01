# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:31:47 by ekeinan           #+#    #+#              #
#    Updated: 2024/11/20 08:50:46 by ekeinan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
BONUS_NAME = .bonus

SRC_CORE = ft_isdigit.c \
		   ft_isalpha.c \
		   ft_isalnum.c \
           ft_isprint.c \
           ft_isascii.c \
           ft_toupper.c \
           ft_tolower.c \
           ft_strlen.c \
           ft_memchr.c \
           ft_memcmp.c \
           ft_strchr.c \
           ft_strrchr.c \
           ft_strncmp.c \
           ft_strnstr.c \
           ft_striteri.c \
		   ft_strmapi.c \
		   ft_atoi.c \
		   ft_itoa.c \
           ft_memcpy.c \
           ft_memmove.c \
           ft_strlcpy.c \
           ft_strlcat.c \
           ft_strdup.c \
           ft_strtrim.c \
           ft_substr.c \
           ft_memset.c \
           ft_bzero.c \
           ft_strjoin.c \
           ft_split.c \
	       ft_calloc.c \
		   ft_putchar_fd.c \
		   ft_putstr_fd.c \
		   ft_putendl_fd.c \
		   ft_putnbr_fd.c

SRC_BONUS = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c

OBJ_CORE = $(SRC_CORE:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

COMPILE_FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	cc $(COMPILE_FLAGS) -c $< -o $@

so:
	$(CC) -nostartfiles -fPIC $(COMPILE_FLAGS) $(SRC_CORE) $(SRC_BONUS)
	gcc -nostartfiles -shared -o libft.so $(OBJ_CORE) $(OBJ_BONUS)

$(NAME): $(OBJ_CORE)
	ar -rcs $(NAME) $(OBJ_CORE)

bonus: ${BONUS_NAME}

${BONUS_NAME}: $(OBJ_CORE) $(OBJ_BONUS)
	ar -rcs $(NAME) $(OBJ_CORE) $(OBJ_BONUS)
	@touch ${BONUS_NAME}

clean:
	rm -f $(OBJ_CORE) ${OBJ_BONUS}
	@rm -f ${BONUS_NAME}

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
