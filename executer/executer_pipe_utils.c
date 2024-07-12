/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:28:21 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/10 10:03:46 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	ft_pipeline_aux(t_ast *ast, t_minishell *minishell, int flag)
{
	pid_t	pid_right;
	int		status;
	int		i;

	i = 0;
	status = 0;
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
	return (status);
}

int	ft_more_pipes(t_ast *ast, t_minishell *minishell, int flag)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	close(ast->token->pipefd[1]);
	ft_pipeline(ast->right, minishell, flag);
	while (i < minishell->pipe_num)
		close(minishell->store_fds[i++]);
	while (wait(&status) > 0)
		continue ;
	return (status);
}

void	ft_pipe_redirection(t_minishell *minishell)
{
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
}
