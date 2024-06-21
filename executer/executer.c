/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:47:22 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/21 19:08:42 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	execute_builtin(t_ast *ast, t_minishell *minishell)
{
	if (ast->right)
		ft_executer(ast->right, minishell);
	if (!ft_strcmp(ast->token->value, "cd"))
		ft_cd(ast, minishell->env, minishell);
	else if (!ft_strcmp(ast->token->value, "pwd"))
		ft_pwd(minishell, minishell->env);
	else if (!ft_strcmp(ast->token->value, "echo"))
		ft_echo(ast, minishell);
	else if (!ft_strcmp(ast->token->value, "env"))
		ft_env(minishell->env, minishell);
	else if (!ft_strcmp(ast->token->value, "export"))
		ft_export(ast, minishell);
	else if (!ft_strcmp(ast->token->value, "unset"))
		ft_unset(ast, minishell);
	else if (!ft_strcmp(ast->token->value, "exit"))
		ft_exit(&minishell, ast);
}

int	check_files_outfile(t_ast *ast, t_minishell *minishell)
{
	if (access(ast->token->value, W_OK) != 0)
	{
		//ft_printf_err("bash: %s: Permission denied\n", ast->token->value);
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(ast->token->value, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		if (minishell->pipe_check == 1)
			exit (1);
		else
			minishell->status = 1;
		return (1);
	}
	return (0);
}

int	check_files(t_ast *ast, t_minishell *minishell)
{
	if (access(ast->token->value, F_OK) != 0)
	{
		//ft_printf_err("bash: %s: No such file or directory\n", ast->token->value);
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(ast->token->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		if (minishell->pipe_check == 1)
			exit (1);
		else
			minishell->status = 1;
		return (1);
	}
	if (access(ast->token->value, R_OK) != 0)
	{
		//ft_printf_err("bash: %s: Permission denied\n", ast->token->value);
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(ast->token->value, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		if (minishell->pipe_check == 1)
			exit (1);
		else
			minishell->status = 1;
		return (1);
	}
	return (0);
}

void	manage_error(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

void	ft_directory(t_ast *ast)
{
	DIR	*dir;

	if (!ast)
		return ;
	if (ast->type == N_DIRECTORY)
	{
		dir = opendir(ast->token->value);
		if (!dir)
			printf("bash: %s: No such file or directory\n", ast->token->value);
		else
			printf("bash: %s: Is a directory\n", ast->token->value);
		closedir(dir);
	}
}

void	ft_executer(t_ast *ast, t_minishell *minishell)
{
	if (!ast)
		return ;
	if (ast->type == N_PIPELINE)
		ft_pipeline(ast, minishell, 0);
	if (ast->type == N_DIRECTORY)
		ft_directory(ast);
	if (ast->type == N_BUILTIN)
		execute_builtin(ast, minishell);
	if (ast->type == N_COMMAND)
		ft_simple_command(ast, minishell);
	if (ast->type == N_REDIRECTION || ast->type == N_HEREDOC)
		ft_redirect(ast, minishell);
}
