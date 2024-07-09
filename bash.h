/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:26:09 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/09 17:55:15 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASH_H
# define BASH_H

# include "include/structs.h"
# include "include/builtin.h"
# include "include/parser_tokenizer.h"
# include "include/expander.h"
# include "include/minishell_utils.h"
# include "libft/include/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdarg.h>
# include <ctype.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termcap.h>
# include <curses.h>
# include <dirent.h>
# include <stdbool.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\033[37m"
# define GREYM		"\x1B[38;5;245m"
# define GREYM2		"\x1B[38;5;250m"
# define BOLD		"\033[1m"
# define RESET		"\x1b[0m"
# define CLEAR		"\033[2J"

//GLOBAL
extern int		g_command_sig;

//executer
void		ft_executer(t_ast *ast, t_minishell *minishell);
void		manage_error(char *error);
int			check_files(t_ast *ast, t_minishell *minishell);
int			check_files_outfile(t_ast *ast, t_minishell *minishell);
void		execute_builtin(t_ast *ast, t_minishell *minishell);

//executer_command_utils
char		*ft_remove_path(char *command);
char		**ft_command_args_aux(t_ast *temp, char **args);
char		**ft_command_args(t_ast *ast);
int			ft_check_path(char **envp);

//executer_command
char		**ft_command_args(t_ast *ast);
void		ft_simple_command2(t_ast *ast, t_minishell *minishell);
void		ft_simple_command(t_ast *ast, t_minishell *minishell);

//executer_pipe_utils
int			ft_more_pipes(t_ast *ast, t_minishell *minishell, int flag);
int			ft_pipeline_aux(t_ast *ast, t_minishell *minishell, int flag);

//executer_pipe
void		ft_pipe_child_left(t_ast *ast, t_minishell *minishell);
void		ft_pipe_child_right(t_ast *ast, t_minishell *minishell);
void		ft_pipeline(t_ast *ast, t_minishell *minishell, int flag);

//executer_redirect
void		ft_open_infile(t_ast *ast, t_minishell *minishell);
void		ft_open_outfile(t_ast *ast, t_minishell *minishell);
void		ft_open_outfile_2(t_ast *ast, t_minishell *minishell);
void		ft_open_heredoc(t_ast *ast, t_minishell *minishell);
void		ft_redirect(t_ast *ast, t_minishell *minishell);

//parser_fda_error
void		print_error_syntax(int level, int state);
void		syntax_problem(t_token *token, int level, int state);

t_ast		*ft_expr(t_input *input);
void		ft_eat(t_input *input, t_tokentype type);

void		print_assignment(t_assign *list);
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

int			check_equal(char *text);
void		ft_expanser(t_minishell *minishell, char **envp);
void		expand_redir(t_ast *ast, t_ast *prev, int flag);

#endif
