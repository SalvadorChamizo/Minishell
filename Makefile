NAME = minishell
CC = clang
FLAGS = -g -Wall -Werror -Wextra -Iinclude #-fsanitize=address
READLINE = -lreadline -ltinfo
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
		tokenizer/tokenizer \
		tokenizer/tokenizer_operator \
		tokenizer/tokenizer_quote \
		tokenizer/tokenizer_utils \
		parser/parser_fda \
		parser/parser_fda_utils \
		parser/parser_fda_error \
		parser/parser_ast \
		parser/parser_ast_utils \
		parser/parser_ast_nodes \
		parser/parser_ast_list \
		parser/parser_underscore \
		parser/parser_underscore_utils \
		parser/print_parser \
		expander/expander_assign_utils \
		expander/expander_assign \
		expander/expander_command \
		expander/expander_directory \
		expander/expander_dollar_env \
		expander/expander_dollar_str_status \
		expander/expander_dollar_str_utils \
		expander/expander_dollar_str \
		expander/expander_dollar_utils \
		expander/expander_heredoc_status \
		expander/expander_heredoc_utils \
		expander/expander_heredoc \
		expander/expander_quotes \
		expander/expander_redirections_fd \
		expander/expander_utils \
		expander/expander \
		executer/builtin/cd/cd \
		executer/builtin/cd/cd_utils \
		executer/builtin/cd/cd_relative \
		executer/builtin/cd/cd_pwd \
		executer/builtin/cd/cd_home \
		executer/builtin/cd/cd_hyphen \
		executer/builtin/pwd/pwd \
		executer/builtin/echo/echo \
		executer/builtin/env/env \
		executer/builtin/export/export \
		executer/builtin/export/export_check \
		executer/builtin/export/export_utils \
		executer/builtin/export/export_print \
		executer/builtin/unset/unset \
		executer/builtin/exit/exit \
		executer/executer \
		executer/executer_command \
		executer/executer_command_utils \
		executer/executer_pipe \
		executer/executer_pipe_utils \
		executer/executer_redirect \
		executer/executer_redirect_utils \
		minishell_utils/logo \
		minishell_utils/minishell_init \
		minishell_utils/minishell_init_extra \
		minishell_utils/sygnal \
		minishell_utils/sygnal_heredoc \
		minishell_utils/free_ast \

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
	@$(CC) $(OBJS) $(LIBFT) $(FLAGS) $(READLINE) -o $(NAME)
	@echo
	@echo "$(MAGENTA)minishell compiled!$(RESET)"
	@echo

bonus: $(NAME_BNS)

$(NAME_BNS): $(LIBFT) $(BNS_OBJS) $(OBJS)
	@$(CC) $(BNS_OBJS) $(LIBFT) $(FLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH) all > /dev/null 2>&1

clean: 
	@rm -f $(OBJS) $(BNS_OBJS)
	@make -C $(LIBFT_PATH) clean > /dev/null 2>&1
	@echo
	@echo "$(RED)Cleaning minishell objects. $(RESET)"

fclean: clean
	@rm -f $(NAME) $(NAME_BNS)
	@make -C $(LIBFT_PATH) fclean > /dev/null 2>&1
	@echo "$(RED)Cleaning minishell executables.$(RESET)"
	@echo

re: fclean all

.PHONY = all clean fclean re libft bonus