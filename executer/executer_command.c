/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:20:55 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/04 16:49:59 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	**ft_command_args(t_ast *ast)
{
	t_ast	*temp;
	char	**args;
	int		i;

	temp = ast;
	i = 0;
	while (temp)
	{
		temp = temp->left;
		i++;
	}
	temp = ast;
	args = malloc(sizeof(char *) * i);
	i = 0;
	while (temp)
	{
		if (temp->token->value != NULL)
			args[i] = temp->token->value;
		temp = temp->left;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	ft_simple_command2(t_ast *ast, t_minishell *minishell)
{
	if (ast->right)
		ft_executer(ast->right, minishell);
	if (ast->type == N_BUILTIN)
	{
		execute_builtin(ast, minishell);
		exit(0);
	}
	else
	{
		if (access(ast->token->value, F_OK | X_OK) != 0)
		{
			printf("Command \"%s\" not found\n", ast->token->value);
			return ;
		}
		execve(ast->token->value, ft_command_args(ast), minishell->env);
	}
}

void	ft_simple_command(t_ast *ast, t_minishell *minishell)
{
	pid_t	pid;
	int		original_stdin;

	original_stdin = dup(STDIN_FILENO);
	if (ast->right)
		ft_executer(ast->right, minishell);
	if (access(ast->token->value, F_OK | X_OK) != 0)
	{
		printf("Command \"%s\" not found\n", ast->token->value);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		execve(ast->token->value, ft_command_args(ast), minishell->env);
	}
	else
	{
		waitpid(pid, NULL, 0);
		dup2(original_stdin, STDIN_FILENO);
	}
}
