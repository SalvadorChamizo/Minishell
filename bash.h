/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:26:09 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/05 15:12:08 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASH_H
# define BASH_H

# include "libft/include/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdarg.h>
# include <ctype.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <dirent.h>

# define RED        "\x1b[31m"
# define GREEN      "\x1b[32m"
# define YELLOW     "\x1b[33m"
# define BLUE       "\x1b[34m"
# define MAGENTA    "\x1b[35m"
# define CYAN       "\x1b[36m"
# define WHITE      "\033[37m"
# define GREYM      "\x1B[38;5;245m"
# define GREYM2     "\x1B[38;5;250m"
# define BOLD       "\033[1m"
# define RESET      "\x1b[0m"
# define CLEAR      "\033[2J"

//GLOBAL
extern volatile sig_atomic_t	g_signal;

//TOKENIZER

typedef enum e_tokentype
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_ASSING,
	T_EOF,
}	t_tokentype;

typedef struct s_token
{
	char		*value;
	t_tokentype	type;
}	t_token;

typedef struct s_input
{
	t_token	*current_token;
	char	*line;
	char	**path;
	int		pos;
	int		error;
}	t_input;

typedef struct s_syntax
{
	t_token			*token;
	struct s_syntax	*left;
	struct s_syntax	*right;
}	t_syntax;

//PARSER

typedef enum e_nodetype
{
	N_IDENTIFIER,
	N_COMMAND,
	N_ARGUMENT,
	N_BUILTIN,
	N_REDIRECTION,
	N_FILE,
	N_HEREDOC,
	N_DELIMITER,
	N_PIPELINE,
	N_ASSIGN,
}	t_nodetype;

typedef struct s_assign_list
{
	char					*variable;
	char					*value;
	struct s_assign_list	*next;
}	t_assign_list;

typedef struct s_ast
{
	t_nodetype		type;
	t_token			*token;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_idenlst
{
	t_token				*token;
	struct s_idenlst	*next;
	struct s_idenlst	*prev;
}	t_idenlst;

typedef struct s_minishell
{
	t_input			*input;
	t_ast			*ast;
	t_assign_list	*list;
	char			**env;
}	t_minishell;

//tokenizer
t_token		*get_next_token(t_input *minishell);
void		ft_skip_spaces(t_input *input, char *text);
void		ft_sop_def(t_input *mshll, t_token *nt, char *rt, t_tokentype t);
void		ft_dop_def(t_input *mshll, t_token *nt, char *rt, t_tokentype t);
void		s_quote_case(t_input *mshll, t_token *nt, char *rt, t_tokentype t);
void		d_quote_case(t_input *mshll, t_token *nt, char *rt, t_tokentype t);
t_token		*tokenizer(t_input minishell);
bool		isoperator(char c);

//space control
int			ft_isspace(char c);
void		ft_skip_spaces(t_input *input, char *text);
int			ft_skip_quote(t_input *input, char *text, t_token *new_token);
int			is_operator(char c);
t_tokentype	ft_operator(char *text);

//parser
int			is_redirection_2(t_token *token);
int			ft_redirection(t_token *token, int state);
int			ft_word(t_token *token, int state);
int			ft_pipe(t_token *token, int state);
int			ft_parents(t_token *token, int state);

int			ft_parser_fda(t_input *input);

//Expanser
void		expand_redir(t_ast *ast, t_ast *prev, int flag);
void		expand_quotes(t_ast *ast);
void		ft_expanser(t_minishell *minishell, char **envp);

//expanser_dollar
int			ft_check_dollar(char *text);
char		*remove_dollar(t_ast *ast);
char		*get_variable(char	*text, int *cur);
void		ft_dollar_list(t_ast *ast, t_assign_list *list, int *flag);
void		ft_dollar(t_ast *ast, t_assign_list *list);

//expanser_assign
void		expand_assignment(t_ast *ast, t_ast *prev);
t_assign_list	*new_assignment(char *text, t_assign_list *list);
void		ft_assign_add_back(t_assign_list **lst, t_assign_list *new);
void		store_assignment(t_ast *ast, t_assign_list **list);

//expanser_command
char		**ft_get_path(char **envp);
void		expand_builtin(t_ast *ast);
void		expand_command(t_ast *ast, t_ast *prev, int flag);
void		expand_command2(t_ast *ast);
void		expand_command_3(t_ast *ast, char **path);

//expanser_utils
int			check_builtin(char *text);
int			check_prev(t_ast *prev);
int			check_prev2(t_ast *prev);
int			check_equal(char *text);
void		ft_store_env(t_assign_list **list, char **envp);

//Builtin
void		ft_cd(t_ast *tree, char **env);
void		cd_error(char *path);
char		*wish_ensambler(char const *s1, char const *s2);
void		regret_basic(t_ast *tree, char **env);
int			ft_chdir(char *order, char **env);
void		ft_pwd(void);
void		ft_echo(t_ast *ast);
void		ft_env(char **env);
void		ft_export(t_ast *ast, char ***env, t_assign_list *list);
int			var_len(char *str);
void		ft_putenv_fd(char *s);
void		export_free(char ***env, int i, int str);
void		ft_unset(t_ast *ast, char ***env, t_assign_list **list);

//executer
void		ft_executer(t_ast *ast, t_minishell *minishell);
void		manage_error(char *error);
int			check_files(t_ast *ast);
void		execute_builtin(t_ast *ast, t_minishell *minishell);

//executer_command
char		**ft_command_args(t_ast *ast);
void		ft_simple_command2(t_ast *ast, t_minishell *minishell);
void		ft_simple_command(t_ast *ast, t_minishell *minishell);

//executer_pipe
void		ft_pipe_child_left(t_ast *ast, t_minishell *minishell, int pipefd[2]);
void		ft_pipe_child_right(t_ast *ast, t_minishell *minishell, int pipefd[2]);
void		ft_pipeline(t_ast *ast, t_minishell *minishell);

//executer_redirect
void		ft_open_infile(t_ast *ast);
void		ft_open_outfile(t_ast *ast);
void		ft_open_outfile_2(t_ast *ast);
void		ft_open_heredoc(t_ast *ast);
void		ft_redirect(t_ast *ast, t_minishell *minishell);

t_ast		*ft_expr(t_input *input);
void		ft_eat(t_input *input, t_tokentype type);

void		print_assignment(t_assign_list *list);
void		print_ast(t_ast *root);
void		print_ast_helper(t_ast *node, int depth, char *side);
void		print_list(t_idenlst *list);

t_ast		*new_i_node(t_token *token);
t_ast		*bi_node(t_ast *left, t_token *op, t_ast *right);
t_ast		*iden_node(t_idenlst *lst);

void		ft_eat_aux(t_input *input);
t_ast		*ft_expr_aux(t_ast *ast, t_ast *ast2, t_idenlst **list);

t_idenlst	*ft_lstnew_identifier(t_token *token);
void		ft_lstadd_identifier(t_idenlst **lst, t_idenlst *new);
void		ft_add_identifier_front(t_idenlst **lst, t_idenlst *new);

t_token		*get_next_token(t_input *input);

int			check_equal(char *text);
void		ft_expanser(t_minishell *minishell, char **envp);
void		expand_redir(t_ast *ast, t_ast *prev, int flag);

//sygnal
int			disable_signal(void);
void		signal_c(int signal_number);
void		signal_slach(int signal_number);

//others
void		ft_enter(void);
void		ft_exit(void);

//memory
void		free_ast(t_ast **ast);
void		*free_split(char **str);
void		ft_list_clear(t_assign_list **list);

#endif
