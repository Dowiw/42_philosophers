# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/30 18:54:17 by kmonjard          #+#    #+#              #
#    Updated: 2025/10/30 18:55:10 by kmonjard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC_FLAGS = -Wall -Werror -Wextra
CC = gcc

SRC_DIR = ./src/

C_FILES = main.c utils.c philosopher.c
C_SRC = $(addprefix $(SRC_DIR), $(C_FILES))

O_FILES = $(C_SRC:.c=.o)

INCLUDES = ./headers

# -- Rules --
all: $(NAME)

$(NAME): $(O_FILES)
	@$(CC) $(CC_FLAGS) $(O_FILES) -o $(NAME)

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CC_FLAGS) -c $< -o $@ -I$(INCLUDES)

clean:
	@echo "Deleting object files in philo..."
	@rm -f $(O_FILES)

fclean:
	@echo "Deleting object files in philo..."
	@echo "Deleting all binaries in philo..."
	@rm -f $(O_FILES)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
