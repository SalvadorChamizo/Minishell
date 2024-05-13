NAME = minishell
CC = gcc
FLAGS = -g -Wall -Werror -Wextra -Iinclude
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
GRAY    = \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD    = \033[1m
RED     = \033[31;1m

FILES =	main \
		exit \
		tokenizer/tokenizer \
		tokenizer/tokenizer_utils \
		tokenizer/tokenizer_quote \
		parser/parser \
		parser/parser_struct \
		parser/node_creator \
		parser/parser_struct_ad \
		parser/syntax_order \
		expanser/expanser \

BNS_FILES = 

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
BNS_SRC_DIR = ./bns/
BNS_SRCS = $(addprefix $(BNS_SRC_DIR), $(addsuffix .c, $(BNS_FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
BNS_OBJ_DIR = ./bns/
BNS_OBJS = $(addprefix $(BNS_OBJ_DIR), $(addsuffix .o, $(BNS_FILES)))

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) -lreadline $(OBJS) $(LIBFT) -o $(NAME)
	@echo
	@echo "$(MAGENTA)minishell compiled!$(RESET)"
	@echo

bonus: $(NAME_BNS)

$(NAME_BNS): $(LIBFT) $(BNS_OBJS) $(OBJS)
	@$(CC) $(FLAGS) $(BNS_OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH) all

clean: 
	@rm -f $(OBJS) $(BNS_OBJS)
	@make -C $(LIBFT_PATH) clean
	@echo "$(RED)Cleaning minishell objects. $(RESET)"

fclean: clean
	@rm -f $(NAME) $(NAME_BNS)
	@make -C $(LIBFT_PATH) fclean
	@echo "$(RED)Cleaning minishell executables.$(RESET)"

re: fclean all

.PHONY = all clean fclean re libft bonus