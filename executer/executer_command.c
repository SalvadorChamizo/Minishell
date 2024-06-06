/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:20:55 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/06 14:21:30 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	*ft_remove_path(char *command)
{
	char	*new_text;
	int	i;
	int len;
	
	i = 0;
	if (command[i] != '/')
		return (command);
	while (command[i])
		i++;
	len = i;
	while (command[i] != '/')
		i--;
	i++;
	len = len - i;
	new_text = malloc(sizeof(char) * len);
	len = 0;
	while (command[i])
	{
		new_text[len] = command[i];
		len++;
		i++;
	}
	new_text[len] = '\0';
	return (new_text);
}

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
		if (temp->token->value != NULL && ft_strcmp(temp->token->value, "") != 0)
			args[i] = ft_remove_path(temp->token->value);
		temp = temp->left;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	ft_simple_command2(t_ast *ast, t_minishell *minishell)
{
	char	*new_text;

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
			new_text = ft_remove_path(ast->token->value);
			printf("Command \'%s\' not found\n", new_text);
			exit(1);
			return ;
		}
		if (execve(ast->token->value, ft_command_args(ast), minishell->env) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
}

void	simple_command_aux(t_ast *ast, t_minishell *minishell, char *new_text)
{
	if (access(ast->token->value, F_OK | X_OK) != 0)
	{
		new_text = ft_remove_path(ast->token->value);
		printf("Command \'%s\' not found\n", new_text);
		exit(127);
	}
	if (execve(ast->token->value, ft_command_args(ast), minishell->env) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void	ft_simple_command(t_ast *ast, t_minishell *minishell)
{
	pid_t	pid;
	char	*new_text;
	int		status;

	new_text = NULL;
	if (ast->right)
		ft_executer(ast->right, minishell);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (!pid)
	{
		simple_command_aux(ast, minishell, new_text);
	}
	else
	{
		waitpid(pid, &status, 0);
		minishell->status = WEXITSTATUS(status);
	}
}
