/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:26:09 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/17 12:08:53 by saroca-f         ###   ########.fr       */
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
}	t_input;

typedef struct s_syntax
{
	t_token			*token;
	struct s_syntax	*left;
	struct s_syntax	*right;
}	t_syntax;



//////////////////////////

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

int			is_redirection(t_token *token);
int			ft_redirection(t_token *token, int state);
int			ft_word(t_token *token, int state);
int			ft_pipe(t_token *token, int state);
int			ft_parents(t_token *token, int state);

t_ast		*ft_expr(t_input *input);
t_ast		*ft_simple_command(t_input *input);
t_ast		*ft_simple_element(t_input *input);
void		ft_eat(t_input *input, t_tokentype type);

void		print_assignment(t_assign_list *list);
void		print_ast(t_ast *root);
void		print_ast_helper(t_ast *node, int depth, char *side);
void		print_list(t_idenlst *list);

t_ast		*create_redirec_node(t_input *input, t_ast *root, t_token *token);
t_ast		*create_word_node(t_input *input, t_token *token, t_nodetype type, int check);
t_ast		*new_i_node(t_token *token);
t_ast		*new_b_node(t_ast *left, t_token *op, t_ast *right);
t_ast		*iden_node(t_idenlst *lst);
t_ast		*new_b_node2(t_ast *left, t_token *op, t_ast *right, t_ast *iden);

void		ft_eat_aux(t_input *input);

t_token		*get_next_token(t_input *input);

int			check_equal(char *text);
void		ft_expanser(t_ast *ast);
void		expand_redir(t_ast *ast, t_ast *prev, int flag);

#endif