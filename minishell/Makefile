NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC_DIR = src
OBJ_DIR = obj
PARSE_SRC_DIR = parse/src
EXEC_SRC_DIR = exec/src

PARSE_SRC_FILES = parse.c \
	free_token.c

EXEC_SRC_FILES = exec.c \

OTHER_SRC_FILES = main.c \
	init.c \
	sig/sig_interactive.c \
	sig/sig_process.c \
	sig/sig_handler.c \
	free/free_cmd.c \
	free/free_env.c \

PARSE_SRC = $(addprefix $(PARSE_SRC_DIR)/, $(PARSE_SRC_FILES))
EXEC_SRC = $(addprefix $(EXEC_SRC_DIR)/, $(EXEC_SRC_FILES))
OTHER_SRC = $(addprefix $(SRC_DIR)/, $(OTHER_SRC_FILES))
SRC_ALL = $(OTHER_SRC) $(PARSE_SRC) $(EXEC_SRC)

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_ALL))

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a

RED = \033[31m
GREEN = \033[1;32m
YELLOW = \033[33m
RESET = \033[0m

all : $(NAME)
	@echo "$(GREEN)✨ minishell ready! ✨$(RESET)"

$(NAME) : $(LIBFT_A) $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFT_DIR) -lft -lreadline -lncurses

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<..."
#	delete g flag
	@$(CC) $(CFLAGS) -c -g $< -o $@

clean :
	@echo "$(RED)Cleaning object folder... 🧹$(RESET)"
	@rm -rf $(OBJ_DIR)/*
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean : clean
	@echo "$(RED)Deleting minishell executable... 🧹⚠️$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY:	all clean fclean all
