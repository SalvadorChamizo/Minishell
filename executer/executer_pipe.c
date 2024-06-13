/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:24:21 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/13 14:59:55 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	ft_pipe_middle(t_ast *ast, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (ast->type != N_COMMAND)
	{
		minishell->pipe_check = 1;
		ft_executer(ast, minishell);
		exit(0);
	}
	if (ast->right)
	{
		minishell->pipe_check = 1;
		ft_executer(ast->right, minishell);
	}
	dup2(ast->token->fd_0, STDIN_FILENO);
	dup2(ast->token->fd_1, STDOUT_FILENO);
	if (minishell->pipe_check == 1)
	{
		if (minishell->infile_check == 1)
		{
			dup2(minishell->stdin_fd, STDIN_FILENO);
			dup2(minishell->fd_in_redir, STDIN_FILENO);
			close(minishell->fd_in_redir);
		}
		if (minishell->outfile_check == 1)
		{
			dup2(minishell->stdout_fd, STDOUT_FILENO);
			dup2(minishell->fd_out_redir, STDOUT_FILENO);
			close(minishell->fd_out_redir);
		}
	}
	minishell->middle_count++;
	while (i < minishell->pipe_num)
		close(minishell->store_fds[i++]);
	ft_simple_command2(ast, minishell);
}

void	ft_pipe_child_left(t_ast *ast, t_minishell *minishell)
{
	int i;

	i = 0;
	if (ast->type != N_COMMAND)
	{
		minishell->pipe_check = 1;
		ft_executer(ast, minishell);
		exit(0);
	}
	if (ast->right)
	{
		minishell->pipe_check = 1;
		ft_executer(ast->right, minishell);
	}
	dup2(ast->token->fd_1, STDOUT_FILENO);
	if (minishell->pipe_check == 1)
	{
		if (minishell->infile_check == 1)
		{
			dup2(minishell->stdin_fd, STDIN_FILENO);
			dup2(minishell->fd_in_redir, STDIN_FILENO);
			close(minishell->fd_in_redir);
		}
		if (minishell->outfile_check == 1)
		{
			dup2(minishell->stdout_fd, STDOUT_FILENO);
			dup2(minishell->fd_out_redir, STDOUT_FILENO);
			close(minishell->fd_out_redir);
		}
	}
	while (i < minishell->pipe_num)
		close(minishell->store_fds[i++]);
	ft_simple_command2(ast, minishell);
}

void	ft_pipe_child_right(t_ast *ast, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (ast->type != N_COMMAND)
	{
		minishell->pipe_check = 1;
		ft_executer(ast, minishell);
		exit(0);
	}
	if (ast->right)
	{
		minishell->pipe_check = 1;
		ft_executer(ast->right, minishell);
	}
	dup2(ast->token->fd_0, STDIN_FILENO);
	if (minishell->pipe_check == 1)
	{
		if (minishell->infile_check == 1)
		{
			dup2(minishell->stdin_fd, STDIN_FILENO);
			dup2(minishell->fd_in_redir, STDIN_FILENO);
			close(minishell->fd_in_redir);
		}
		if (minishell->outfile_check == 1)
		{
			dup2(minishell->stdout_fd, STDOUT_FILENO);
			dup2(minishell->fd_out_redir, STDOUT_FILENO);
			close(minishell->fd_out_redir);
		}
	}
	while (i < minishell->pipe_num)
		close(minishell->store_fds[i++]);
	ft_simple_command2(ast, minishell);
}

void	ft_pipeline(t_ast *ast, t_minishell *minishell, int flag)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;
	int		i;

	status = 0;
	i = 0;
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
			close(ast->token->pipefd[1]);
			ft_pipeline(ast->right, minishell, 1);
			while (i < minishell->pipe_num)
					close(minishell->store_fds[i++]);
			while (wait(&status) > 0)
				continue ;
		}
		else
		{
			close(ast->token->pipefd[1]);
			pid_right = fork();
			if (!pid_right)
				ft_pipe_child_right(ast->right, minishell);
			else
			{
				while (i < minishell->pipe_num)
					close(minishell->store_fds[i++]);
				if (flag == 0)
					while (wait(&status) > 0)
						continue ;
			}
		}
	}
	minishell->status = WEXITSTATUS(status);
}
