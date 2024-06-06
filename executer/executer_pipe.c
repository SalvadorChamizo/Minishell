/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:24:21 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/06 14:03:53 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	ft_pipe_child_left(t_ast *ast, t_minishell *minishell, int pipefd[2])
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	ft_simple_command2(ast, minishell);
	//execve(ast->token->value, ft_command_args(ast), *env);
}

void	ft_pipe_child_right(t_ast *ast, t_minishell *minishell, int pipefd[2])
{
	int		original_stdin;
	int		original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	if (ast->type == N_PIPELINE)
		ft_pipeline(ast, minishell);
	else
	{
		ft_simple_command2(ast, minishell);
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
	}
	//execve(ast->token->value, ft_command_args(ast), *env);
}

void	ft_pipeline(t_ast *ast, t_minishell *minishell)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
		manage_error("pipe");
	pid_left = fork();
	if (!pid_left)
		ft_pipe_child_left(ast->left, minishell, pipefd);
	else
	{
		pid_right = fork();
		if (!pid_right)
			ft_pipe_child_right(ast->right, minishell, pipefd);
		else
		{
			close(pipefd[0]);
			close(pipefd[1]);
			waitpid(pid_left, &status, 0);
			waitpid(pid_right, &status, 0);
			minishell->status = WEXITSTATUS(status);
		}
	}
}
