/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:20:55 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/10 18:39:37 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	print_error_command(t_minishell *minishell, char *text)
{
	if (!ft_check_path(minishell->env))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(text, 2);
		ft_putstr_fd(": No such file or directoty\n", 2);
	}
	else
	{
		ft_putstr_fd("Command \'", 2);
		ft_putstr_fd(text, 2);
		ft_putstr_fd("\' not found\n", 2);
	}
}

void	ft_simple_command2(t_ast *ast, t_minishell *minishell)
{
	char	*new_text;
	char	*value;

	value = ast->token->value;
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
			print_error_command(minishell, new_text);
			exit(127);
		}
		if (execve(value, ft_command_args(ast), minishell->env) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
}

void	simple_command_aux(t_ast *ast, t_minishell *minishell, char *new_text)
{
	char	**args;

	args = NULL;
	if (ast->right)
	{
		minishell->pipe_check = 1;
		ft_executer(ast->right, minishell);
	}
	if (access(ast->token->value, F_OK | X_OK) != 0)
	{
		new_text = ft_remove_path(ast->token->value);
		print_error_command(minishell, new_text);
		exit(127);
	}
	args = ft_command_args(ast);
	if (execve(*args, args, minishell->env) == -1)
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
	pid = fork();
	g_command_sig = pid;
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (!pid)
		simple_command_aux(ast, minishell, new_text);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			minishell->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			minishell->status = WTERMSIG(status) + 128;
	}
}
