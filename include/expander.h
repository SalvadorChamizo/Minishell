/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:52:08 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/10 10:18:52 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

//expander

void		remove_empty_node(t_ast *ast, t_ast *prev);
int			check_assign_aux(t_ast *ast, char **env, int j, int i);
int			check_assign_env(t_ast *ast, char **env);
void		ft_expander(t_minishell *minishell, char **envp);
//expander_utils

int			check_builtin(char *text);
int			check_prev(t_ast *prev);
int			check_prev2(t_ast *prev);
int			check_equal(char *text);
void		ft_store_env(t_assign **list, char **envp);

//expander_assign_utils

void		quote_manage(char c, int *flag, int *i);
int			new_value_size(char *value);
void		get_new_value(char *value, char **new_value);
char		*lst_addiction(char *value, char *text, int i);
bool		list_act(char *text, int i, t_assign *temp, char *word);

//expander_assign

void		assigment_value(t_ast *ast);
void		expand_assignment(t_ast *ast, t_ast *prev);
t_assign	*new_assignment(char *text, t_assign *list);
void		ft_assign_add_back(t_assign **lst, t_assign *new);
void		store_assignment(t_ast *ast, t_assign **list);

//expander_command

char		**ft_get_path(char **envp);
void		expand_builtin(t_ast *ast);
void		expand_command(t_ast *ast, t_ast *prev, int flag);
void		expand_command2(t_ast *ast);
void		expand_command_3(t_ast *ast, char **path);

//expander_directory

bool		is_command(const char *path);
bool		ft_expanser_directory(t_ast *ast);

//expander_dollar_env

char		*get_variable_env(char	*text);
char		*get_value_env(char *text);
int			env_variable_loop(t_dollar *dollar, char *new_text, char **env);
void		env_variable(char **env, \
t_dollar *dollar, char *new_text, char *str);

//expander_dollar_str_status

char		*init_status(t_dollar **dollar);
void		loop_status(char *s, t_minishell *mnshll, \
t_dollar *dollar, char *text);
char		*expand_status_str(char *str, t_minishell *minishell);

//expander_dollar_str_utils

int			ft_skip_quote(char *str, char *new_text, int *i, int k);
char		*remove_dollar_str(char	*str);
void		ft_search_aux(char **env, t_dollar *dollar, \
char *new_text, int *flag);
void		ft_search_env(char **env, t_dollar *dollar, \
char *new_text, char *str);
void		init_dollar(t_dollar **dollar, char **new_text, int *flag);

//expander_dollar_str

void		process_env(char *str, char *new_text, \
t_dollar *dollar, char **env);
char		*str_dollar_env(char *str, char **env, int *flag);
void		process_list(char *str, t_assign *list, \
t_dollar *dollar, char *text);
char		*str_dollar_list(char *str, t_assign *list, int *flag);
char		*ft_expand_str(char *str, t_minishell *minishell);

//expander_dollar_utils

int			ft_check_dollar(char *text);
void		copy_variable(t_assign *temp, \
t_dollar *dollar, char *text, char *str);
void		check_variable_copy(t_dollar *dollar, \
char *text, t_minishell *mnshll);
char		*get_variable(char	*text, int *cur);

//expander_heredoc_status

char		*status_heredoc_free(char *new_text, char *str);
char		*expand_status_heredoc(char *str, t_minishell *minishell);

//expander_heredoc_utils

void		write_heredoc_exit(char *buffer, int line_number);
void		reopen_heredoc(t_minishell *minishell, char *name);
void		ft_write_heredoc(t_ast *ast, t_minishell *minishell, char *name);
void		store_heredoc_aux(t_ast *ast, \
t_minishell *mnshll, char *name, int pid);
int			ft_store_heredoc(t_ast *ast, t_minishell *minishell, int num);

//expander_heredoc

char		*remove_dollar_heredoc(char	*str);
char		*heredoc_dollar_env(char *str, char **env, int *flag);
char		*heredoc_dollar_list(char *str, t_assign *list, int *flag);
char		*ft_expand_heredoc(char *str, t_minishell *minishell);

//expander_quotes

char		*expand_quotes_str(char *str);
void		expand_quotes(t_ast *ast);

//expander_redirections_fd

void		expand_redir(t_ast *ast, t_ast *prev, int flag);
int			count_pipes(t_ast *ast);
void		ft_store_fds(t_ast *ast, t_minishell *minishell);
void		expand_pipefd(t_ast *ast, int flag);
