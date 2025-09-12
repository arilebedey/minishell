NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj

SRC = ft_isalpha.c \
ft_isdigit.c \
ft_isalnum.c \
ft_isascii.c \
ft_isspace.c \
ft_isprint.c \
ft_strlen.c \
ft_strlen2.c \
ft_memset.c \
ft_bzero.c \
ft_memcpy.c \
ft_memmove.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_toupper.c \
ft_tolower.c \
ft_strchr.c \
ft_strchr2.c \
ft_strrchr.c \
ft_strncmp.c \
ft_strndup.c \
ft_memchr.c \
ft_memcmp.c \
ft_strnstr.c \
ft_atoi.c \
ft_atoll.c \
ft_calloc.c \
ft_strdup.c \
ft_substr.c \
ft_strjoin.c \
ft_strtrim.c \
ft_itoa.c \
ft_split.c \
ft_strmapi.c \
ft_striteri.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_printf/ft_printf.c \
ft_printf/printers.c \
ft_printf/printers2.c \
ft_printf/printers3.c \
ft_printf/printers4.c \
gnl/get_next_line_bonus.c \
gnl/get_next_line_utils_bonus.c \
ft_realloc.c \

SRC_BONUS = ft_lstnew_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstadd_back_bonus.c \
ft_lstlast_bonus.c \
ft_lstsize_bonus.c \
ft_lstdelone_bonus.c \
ft_lstclear_bonus.c \
ft_lstiter_bonus.c \
ft_lstmap_bonus.c

SRC_ALL = $(SRCS) $(SRCS_BONUS)

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_BONUS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_BONUS))

RED = \033[3;31m
YELLOW = \033[3;33m
CYAN = \033[1;3;36m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_BONUS)
	@echo "$(YELLOW)LIBFT: Creating archive...$(RESET)"
	@ar rcs $@ $^
	@echo "$(CYAN)LIBFT: Archive created!$(RESET) ✅​"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)LIBFT: Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c -g $< -o $@

clean:
	@echo "$(RED)LIBFT: Cleaning object folder...$(RESET) 🧹"
	@rm -rf $(OBJ_DIR)/*

fclean: clean
	@echo "$(RED)LIBFT: Deleting archive...$(RESET) 🧹⚠️​"
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean all
