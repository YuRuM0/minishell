# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flima <flima@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 20:28:14 by flima             #+#    #+#              #
#    Updated: 2025/03/11 16:19:59 by flima            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m

FLAGS = -Wall -Werror -Wextra -g
# FLAGS += -fsanitize=address

LIBFT_DIR = Libft
LIBFT = LIBFT_DIR/libft.a

INCLUDE = includes

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

SRC_FILES = $(PARSE_FILES) $(ERROR_FILE) $(JUMP_PARSE_FILES) \
				$(PARSE_UTILS_FILES) $(DEBUG_FILES)

OBJS_DIR = objs
OBJS = $(patsubst $(SCRS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRC_FILES))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "\n$(BLUE)Compiling minishell program...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDE) -o $(NAME)
	@echo "$(GREEN)minishell  [OK]$(RESET)\n"

$(OBJS_DIR)/%.o: $(SCRS_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	@echo "$(GREEN)Compiling: $< into $@$(RESET)"

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	@$(MAKE) --no-print-directory clean -C Libft
	@if [ -d $(OBJS_DIR) ]; then \
		echo "\n$(GREEN)Object files have been removed   [OK]$(RESET)\n"; \
	fi
	@rm -rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) --no-print-directory fclean -C Libft
	@rm -f $(NAME)
	@echo "\n$(GREEN)Executable file has been removed [OK]$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re