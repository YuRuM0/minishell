# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flima <flima@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 20:28:14 by flima             #+#    #+#              #
#    Updated: 2025/03/11 14:53:10 by flima            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Werror -Wextra -g
# FLAGS += -fsanitize=address

LIBFT_DIR = Libft
LIBFT = LIBFT_DIR/libft.a

INCLUDES = includes

SCRS_DIR = srcs
PARSE_DIR = $(SCRS_DIR)/parsing
PARSE_FILES = $(PARSE_DIR)/main.c \
				$(PARSE_DIR)/parse.c \
				$(PARSE_DIR)/tokenization.c
				
ERROR_DIR = $(PARSE_DIR)/error_handling
ERROR_FILE = $(ERROR_DIR)/errors_handler.c

JUMP_PARSE_DIR = $(PARSE_DIR)/jump_table_token
JUMP_PARSE_FILES = $(JUMP_PARSE_DIR)/process_tokens01.c \
					$(JUMP_PARSE_DIR)/process_tokens02.c
					
PARSE_UTILS_DIR = $(PARSE_DIR)/parse_utils
PARSE_UTILS_FILES = $(PARSE_UTILS_DIR)/utils_parse.c \
					$(PARSE_UTILS_DIR)/utils_token_list.c

DEBUG_DIR = $(PARSE_DIR)/debugging
DEBUG_FILES = $(DEBUG_DIR)/print_tokens.c

SRC_FILES = $(PARSE_FILES) $(ERROR_FILE) $(JUMP_PARSE_DIR) \
				$(PARSE_UTILS_FILES) $(DEBUG_FILES)

