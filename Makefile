NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP -Iinclude -Iparse/include -Iexec/include -Ilibft

SRC_DIR = src
OBJ_DIR = obj
PARSE_SRC_DIR = parse/src
EXEC_SRC_DIR = exec/src

PARSE_SRC_FILES = parse.c \
	command.c \
	init_structs.c \
	token.c \
	lexer/lexer.c \
	lexer/lexer_word.c \
	lexer/lexer_special.c \
	build/build.c \
	build/build_handler.c \
	build/build_error.c \
	expander/expander.c \
	expander/replace.c \

EXEC_SRC_FILES = exec.c \
	pipeline/pipeline.c \
	pipeline/utils.c \
	exec_command.c \
	setup_redirs.c \
	args_to_argv.c \
	env_to_envp.c \
	heredocs/process.c \
	heredocs/write_heredocs.c \
	heredocs/write_utils.c \
	cmd/get_cmd.c \
	builtins/try_exec_builtins.c \
	builtins/helpers.c \
	builtins/b_exit.c \
	builtins/b_cd.c \
	builtins/b_cd_utils.c \
	builtins/b_echo.c \
	builtins/b_env.c \
	builtins/b_export.c \
	builtins/b_export_setvar.c \
	builtins/b_export_utils.c \
	builtins/b_pwd.c \
	builtins/b_unset.c \

OTHER_SRC_FILES = main.c \
	error.c \
	free_cmd.c \
	env/init_env.c \
	env/free_env.c \
	env/get_env.c \
	sig/sig_interactive.c \
	sig/sig_process.c \
	sig/sig_handler.c \
	debug/debug_token.c \
	debug/debug_cmd.c \
	debug/debug_env.c \

PARSE_SRC = $(addprefix $(PARSE_SRC_DIR)/, $(PARSE_SRC_FILES))
EXEC_SRC = $(addprefix $(EXEC_SRC_DIR)/, $(EXEC_SRC_FILES))
OTHER_SRC = $(addprefix $(SRC_DIR)/, $(OTHER_SRC_FILES))
SRC_ALL = $(OTHER_SRC) $(PARSE_SRC) $(EXEC_SRC)

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_ALL))
DEP = $(OBJ:.o=.d)

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin) # macOS
	READLINE_DIR = $(shell brew --prefix readline)
	CFLAGS += -I$(READLINE_DIR)/include
	LDFLAGS += -L$(READLINE_DIR)/lib
endif

LDFLAGS += -lreadline -lhistory -lncurses

RED = \033[31m
GREEN = \033[1;32m
YELLOW = \033[33m
RESET = \033[0m

all : $(NAME)
	@echo "$(GREEN)✨ minishell ready! ✨$(RESET)"

$(NAME) : $(LIBFT_A) $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFT_DIR) -lft $(LDFLAGS)

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c -g $< -o $@

clean :
	@echo "$(RED)Cleaning object folder... 🧹$(RESET)"
	@rm -rf $(OBJ_DIR)/*
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean : clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "$(RED)Deleting minishell executable... 🧹⚠️$(RESET)"
	@rm -f $(NAME)

re:	fclean all

-include $(DEP)

.PHONY:	all clean fclean re
