# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 15:47:11 by aarmitan          #+#    #+#              #
#    Updated: 2025/04/10 15:50:59 by aarmitan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

# Compilateur et flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3
LDFLAGS		= -lreadline -Llibft -lft

# Dossiers
SRC_DIR		= SRCS
OBJ_DIR		= obj
LIBFT_DIR	= libft

# Recherche tous les fichiers .c dans SRCS/ et ses sous-dossiers
SRC			= $(shell find $(SRC_DIR) -name '*.c')
OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Headers (ajoute celui de libft si nécessaire)
INCLUDES	= -I$(SRC_DIR) -I$(LIBFT_DIR)

# Commande de compilation avec création auto du dossier obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation globale
all: $(LIBFT_DIR)/libft.a $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;33m\nCOMPILING MINISHELL...\n"
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "\033[1;32m./minishell created\n"

# Compilation de libft
$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR)

# Nettoyage
clean:
	@echo "\033[0;31mDeleting object files...\n"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[1;32mDone\n"

fclean: clean
	@echo "\033[0;31mDeleting executable...\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[1;32mDone\n"

re: fclean all

.PHONY: all clean fclean re
