/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:52:08 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/08 18:45:28 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

//expanser

void		expand_redir(t_ast *ast, t_ast *prev, int flag);
void		expand_quotes(t_ast *ast);
void		remove_empty_node(t_ast *ast, t_ast *prev);
int			check_assign_env(t_ast *ast, char **env);
int			count_pipes(t_ast *ast);
void		ft_store_fds(t_ast *ast, t_minishell *minishell);
void		expand_pipefd(t_ast *ast, int flag);
int			ft_store_heredoc(t_ast *ast, t_minishell *minishell, int num);
void		ft_expanser(t_minishell *minishell, char **envp);

//expanser_utils

int			check_builtin(char *text);
int			check_prev(t_ast *prev);
int			check_prev2(t_ast *prev);
int			check_equal(char *text);
void		ft_store_env(t_assign **list, char **envp);

//expanser_heredoc

char		*remove_dollar_heredoc(char	*str);
char		*heredoc_dollar_env(char *str, char **env, int *flag);
char		*heredoc_dollar_list(char *str, t_assign *list, int *flag);
char		*expand_status_heredoc(char *str, t_minishell *minishell);
char		*ft_expand_heredoc(char *str, t_minishell *minishell);

//expanser_dollar

char		*remove_dollar(t_ast *ast);
char		*get_variable(char	*text, int *cur);
void		ft_dollar_list(t_ast *ast, t_assign *list, int *flag);
void		dollar_exit_status(t_ast *ast, t_minishell *minishell);
char		*get_variable_env(char	*text);
char		*get_value_env(char *text);
void		check_variable_env(char **env, t_dollar *dollar, char *new_text, char *str);
void		ft_dollar_env(t_ast *ast, char **env, int *flag);
void		ft_dollar(t_ast *ast, t_assign *list, t_minishell *minishell);

//expanser_dollar_utils

int			ft_check_dollar(char *text);
void		check_variable_copy2(t_assign *temp, t_dollar *dollar, char *new_text, char *str);
void		check_variable_copy(t_dollar *dollar, char *new_text, t_minishell *minishell);

//expanser_dollar_str

char		*remove_dollar_str(char	*str);
char		*str_dollar_env(char *str, char **env, int *flag);
char		*str_dollar_list(char *str, t_assign *list, int *flag);
char		*expand_status_str(char *str, t_minishell *minishell);
char		*ft_expand_str(char *str, t_minishell *minishell);

//expanser_directory

bool		is_command(const char *path);
bool		ft_expanser_directory(t_ast *ast);

//expanser_command

char		**ft_get_path(char **envp);
void		expand_builtin(t_ast *ast);
void		expand_command(t_ast *ast, t_ast *prev, int flag);
void		expand_command2(t_ast *ast);
void		expand_command_3(t_ast *ast, char **path);

//expanser_assign

void		assigment_value(t_ast *ast);
void		expand_assignment(t_ast *ast, t_ast *prev);
t_assign	*new_assignment(char *text, t_assign *list);
void		ft_assign_add_back(t_assign **lst, t_assign *new);
void		store_assignment(t_ast *ast, t_assign **list);

//expanser_assign_utils

void		quote_manage(char c, int *flag, int *i);
int			new_value_size(char *value);
void		get_new_value(char *value, char **new_value);
char		*lst_addiction(char *value, char *text, int i);
bool		list_act(char *text, int i, t_assign *temp, char *word);
