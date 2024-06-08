/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:47:22 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/08 15:46:51 by schamizo         ###   ########.fr       */
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
		ft_pwd(minishell);
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

int	check_files(t_ast *ast)
{
	if (access(ast->token->value, F_OK) != 0)
	{
		printf("bash: %s: No such file or directory\n", ast->token->value);
		return (1);
	}
	if (access(ast->token->value, R_OK) != 0)
	{
		ft_printf("bash: %s: Permission denied\n", ast->token->value);
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
	DIR *dir;

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
	{
		ft_pipeline(ast, minishell);
	}
	if (ast->type == N_DIRECTORY)
	{
		ft_directory(ast);
	}
	if (ast->type == N_BUILTIN)
	{
		execute_builtin(ast, minishell);
	}
	if (ast->type == N_COMMAND)
	{
		ft_simple_command(ast, minishell);
	}
	if (ast->type == N_REDIRECTION || ast->type == N_HEREDOC)
	{
		ft_redirect(ast, minishell);
	}
}
