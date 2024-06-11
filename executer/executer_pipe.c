/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:24:21 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/11 14:24:32 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	ft_pipe_middle(t_ast *ast, t_minishell *minishell)
{
	close(minishell->pipe_in[1]);
	dup2(minishell->pipe_in[0], STDIN_FILENO);
	close(minishell->pipe_out[0]);
	dup2(minishell->pipe_out[1], STDOUT_FILENO);
	close(minishell->pipe_in[0]);
	close(minishell->pipe_out[1]);
	ft_simple_command2(ast, minishell);
}

void	ft_pipe_child_left(t_ast *ast, t_minishell *minishell)
{
	close(minishell->pipe_out[0]);
	close(minishell->pipe_out[1]);
	close(minishell->pipe_in[0]);
	dup2(minishell->pipe_in[1], STDOUT_FILENO);
	close(minishell->pipe_in[1]);
	ft_simple_command2(ast, minishell);
}

void	ft_pipe_child_right(t_ast *ast, t_minishell *minishell, int flag)
{
	if (flag == 1)
	{
		close(minishell->pipe_in[0]);
		close(minishell->pipe_in[1]);
		close(minishell->pipe_out[1]);
		dup2(minishell->pipe_out[0], STDIN_FILENO);
		close(minishell->pipe_out[0]);
	}
	if (flag == 0)
	{
		close(minishell->pipe_out[0]);
		close(minishell->pipe_out[1]);
		close(minishell->pipe_in[1]);
		dup2(minishell->pipe_in[0], STDIN_FILENO);
		close(minishell->pipe_in[0]);
	}
	ft_simple_command2(ast, minishell);
}

void	ft_pipeline(t_ast *ast, t_minishell *minishell, int flag)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	status = 0;
	if (flag == 0)
	{
		if (pipe(minishell->pipe_in) == -1)
			manage_error("pipe");
		if (pipe(minishell->pipe_out) == -1)
			manage_error("pipe");
	}
	pid_left = fork();
	if (!pid_left)
	{
		if (flag == 1)
			ft_pipe_middle(ast->left, minishell);
		else
			ft_pipe_child_left(ast->left, minishell);
	}
	else
	{
		if (ast->right->type == N_PIPELINE)
		{
			ft_pipeline(ast->right, minishell, 1);
			while (wait(&status) > 0)
				continue ;
		}
		else
		{
			if (flag == 0)
			{
				close(minishell->pipe_in[1]);
				close(minishell->pipe_out[0]);
				close(minishell->pipe_out[1]);
			}
			pid_right = fork();
			if (!pid_right)
				ft_pipe_child_right(ast->right, minishell, flag);
			else
			{
				close(minishell->pipe_in[0]);
				close(minishell->pipe_in[1]);
				close(minishell->pipe_out[0]);
				close(minishell->pipe_out[1]);
				if (flag == 0)
					while (wait(&status) > 0)
						continue ;
			}
		}
	}
	minishell->status = WEXITSTATUS(status);
}
