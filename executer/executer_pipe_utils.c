/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:28:21 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/13 15:48:05 by schamizo         ###   ########.fr       */
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
