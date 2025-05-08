# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flima <flima@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 20:28:14 by flima             #+#    #+#              #
#    Updated: 2025/05/08 20:34:11 by flima            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m

CFLAGS = -Wall -Werror -Wextra -g
# CFLAGS += -fsanitize=address

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDE = includes
HEADERS = $(INCLUDE)/libft.h \
			$(INCLUDE)/minishell.h \
			$(INCLUDE)/tokenization.h \
			$(INCLUDE)/execution.h

SCRS_DIR = srcs
PARSE_DIR = $(SCRS_DIR)/parsing
PARSE_FILES = $(PARSE_DIR)/main.c \
				$(PARSE_DIR)/parse.c \
				$(PARSE_DIR)/tokenization.c \
				$(PARSE_DIR)/syntax.c

ENVIRONMENT_VAR_DIR = $(PARSE_DIR)/env_variables
ENVIRONMENT_VAR_FILES = $(ENVIRONMENT_VAR_DIR)/env_var_utils.c \
						$(ENVIRONMENT_VAR_DIR)/environment_var.c \
						$(ENVIRONMENT_VAR_DIR)/env_expand_utils.c \
						$(ENVIRONMENT_VAR_DIR)/create_envp_array.c

HEREDORC_DIR = $(PARSE_DIR)/heredoc_handler
HEREDOC_FILES = $(HEREDORC_DIR)/heredoc_handle.c \
					$(HEREDORC_DIR)/heredoc_read_input.c

COMMANDS_DIR = $(PARSE_DIR)/commands_builder
COMMANDS_FILES = $(COMMANDS_DIR)/commands_builder.c\
					$(COMMANDS_DIR)/utils_commands_list.c

ERROR_DIR = $(PARSE_DIR)/error_handling
ERROR_FILE = $(ERROR_DIR)/errors_handler.c

JUMP_PARSE_DIR = $(PARSE_DIR)/jump_tables
JUMP_PARSE_FILES = $(JUMP_PARSE_DIR)/process_tokens01.c \
					$(JUMP_PARSE_DIR)/process_tokens02.c \
					$(JUMP_PARSE_DIR)/syntax_check.c

PARSE_UTILS_DIR = $(PARSE_DIR)/parse_utils
PARSE_UTILS_FILES = $(PARSE_UTILS_DIR)/utils_parsing.c \
					$(PARSE_UTILS_DIR)/utils_token_list.c \
					$(PARSE_UTILS_DIR)/utils_errors_handler.c \
					$(PARSE_UTILS_DIR)/utils_especial_char.c \
					$(PARSE_UTILS_DIR)/setup_file_descriptors.c \
					$(PARSE_UTILS_DIR)/merge_tokens.c

DEBUG_DIR = $(PARSE_DIR)/debugging
DEBUG_FILES = $(DEBUG_DIR)/print_tokens.c \
				$(DEBUG_DIR)/debug_utils.c

FREE_DIR = $(PARSE_DIR)/free_memory
FREE_FILE = $(FREE_DIR)/free_parse.c

SIGNAL_DIR = $(PARSE_DIR)
SIGNAL_FILES = $(SIGNAL_DIR)/signal.c


EXEC_DIR = $(SCRS_DIR)/execution
EXEC_FILES = $(EXEC_DIR)/manage_builtins.c\
				$(EXEC_DIR)/execution.c\
				$(EXEC_DIR)/executable_path.c\
				$(EXEC_DIR)/child_executor.c\
				$(EXEC_DIR)/exec_pipeline.c \
				$(EXEC_DIR)/exec_utils.c

BUILTIN_DIR = $(EXEC_DIR)/builtins
BUILTIN_FILES = $(BUILTIN_DIR)/echo.c \
				$(BUILTIN_DIR)/env_utils.c \
				$(BUILTIN_DIR)/env.c \
				$(BUILTIN_DIR)/exit.c \
				$(BUILTIN_DIR)/export.c \
				$(BUILTIN_DIR)/export_utils.c \
				$(BUILTIN_DIR)/pwd.c \
				$(BUILTIN_DIR)/unset.c \
				$(BUILTIN_DIR)/cd_main.c \
				$(BUILTIN_DIR)/cd_utils.c


SRC_FILES = $(PARSE_FILES) $(ERROR_FILE) $(JUMP_PARSE_FILES) \
				$(PARSE_UTILS_FILES) $(DEBUG_FILES) $(FREE_FILE) \
				$(ENVIRONMENT_VAR_FILES) $(COMMANDS_FILES) \
				$(BUILTIN_FILES) $(CONNECT_FILES) $(SIGNAL_FILES) \
				$(EXEC_FILES) $(HEREDOC_FILES)

OBJS_DIR = objs
OBJS = $(patsubst $(SCRS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRC_FILES))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I$(INCLUDE) -lreadline -o $(NAME)
	@echo "\n$(GREEN)minishell  ✅$(RESET)\n"

$(OBJS_DIR)/%.o: $(SCRS_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	@echo "$(GREEN)Compiling: $< into $@$(RESET)"

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	@$(MAKE) --no-print-directory clean -C Libft
	@if [ -d $(OBJS_DIR) ]; then \
		echo "$(YELLOW)Object files have been removed   ✅$(RESET)"; \
	fi
	@rm -rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) --no-print-directory fclean -C Libft
	@rm -f $(NAME)
	@echo "$(YELLOW)Executable file has been removed ✅$(RESET)"

re: fclean all
	@echo "$(GREEN)Rebuild complete! All files cleaned and recompiled ✅$(RESET)\n"
.PHONY: all clean fclean re
