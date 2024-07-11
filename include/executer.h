/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:05:11 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/11 11:33:26 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

//executer

void	execute_builtin(t_ast *ast, t_minishell *minishell);
int		check_files(t_ast *ast, t_minishell *minishell);
void	manage_error(char *error);
void	ft_directory(t_ast *ast, t_minishell *minishell);
void	ft_executer(t_ast *ast, t_minishell *minishell);

//executer_command

void	print_error_command(t_minishell *minishell, char *text);
void	ft_simple_command2(t_ast *ast, t_minishell *minishell);
void	simple_command_aux(t_ast *ast, t_minishell *minishell, char *new_text);
void	ft_simple_command(t_ast *ast, t_minishell *minishell);

//executer_command_utils

char	*ft_remove_path(char *command);
char	*command_args_builder(t_ast **temp, int flag);
char	**ft_command_args_aux(t_ast *temp, char **args);
char	**ft_command_args(t_ast *ast);
int		ft_check_path(char **envp);

//executer_pipe

void	ft_pipe_middle(t_ast *ast, t_minishell *minishell);
void	ft_pipe_child_left(t_ast *ast, t_minishell *minishell);
void	ft_pipe_child_right(t_ast *ast, t_minishell *minishell);
void	ft_pipeline(t_ast *ast, t_minishell *minishell, int flag);

//executer_pipe_utils

int		ft_pipeline_aux(t_ast *ast, t_minishell *minishell, int flag);
int		ft_more_pipes(t_ast *ast, t_minishell *minishell, int flag);
void	ft_pipe_redirection(t_minishell *minishell);

//executer_redirect

void	ft_open_infile(t_ast *ast, t_minishell *minishell);
void	ft_open_outfile(t_ast *ast, t_minishell *minishell);
void	ft_open_outfile_2(t_ast *ast, t_minishell *minishell);
void	ft_redirect(t_ast *ast, t_minishell *minishell);

//executer_redirect_utils

void	ft_open_outfile_aux(t_ast *ast, t_minishell *minishell);
void	ft_open_outfile_2_aux(t_ast *ast, t_minishell *minishell);
int		check_files_outfile(t_ast *ast, t_minishell *minishell);
