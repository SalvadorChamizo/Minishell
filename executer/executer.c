/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:47:22 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/30 10:05:07 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	execute_builtin(t_ast *ast, char ***env)
{
	if (!ft_strcmp(ast->token->value, "cd"))
		ft_cd(ast, *env);
	else if (!ft_strcmp(ast->token->value, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(ast->token->value, "echo"))
		ft_echo(ast);
	else if (!ft_strcmp(ast->token->value, "env"))
		ft_env(*env);
	else if (!ft_strcmp(ast->token->value, "export"))
		ft_export(ast, env);
	/*else if (!ft_strcmp(ast->token->value, "unset"))
		ft_unset(ast->right);
	else if (!ft_strcmp(ast->token->value, "exit"))
		ft_exit(ast->right);*/
}

void	ft_command(t_ast *ast, char ***env)
{
	pid_t	pid;
	char	**args;
	t_ast	*temp;
	int		cont;
	int		i;

	cont = 0;
	i = 0;
	temp = ast;
	if (ast->right)
	{
		ft_executer(ast->right, env);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		while (temp)
		{
			temp = temp->left;
			cont++;
		}
		temp = ast;
		args = malloc(sizeof(char *) * cont);
		while (temp)
		{
			args[i] = temp->token->value;
			temp = temp->left;
			i++;
		}
		execve(ast->token->value, args, *env);
	}
}

void	ft_pipeline(t_ast *ast, char ***env)
{
	if (ast->type == N_PIPELINE)
	{
		ft_pipeline(ast->left, env);
		ft_pipeline(ast->right, env);
	}
	if (ast->type == N_HEREDOC || ast->type == N_REDIRECTION)
	{

	}
	if (ast->type == N_COMMAND)
	{
		ft_command(ast, env);
	}
	if (ast->type == N_BUILTIN)
	{
		execute_builtin(ast, env);
	}
}


void	ft_executer(t_ast *ast, char ***env)
{
	if (ast->type == N_PIPELINE)
	{
		ft_executer(ast->left, env);
		ft_executer(ast->right, env);
	}
	if (ast->type == N_BUILTIN)
	{
		printf("Entra\n");
		execute_builtin(ast, env);
	}
	if (ast->type == N_COMMAND)
	{
		printf("Entra 2\n");
		ft_command(ast, env);
	}
}