/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:24:21 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/10 10:04:20 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

/*void	ft_child_aux(t_ast *ast, t_minishell *minishell)
{
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
}*/

void	ft_pipe_middle(t_ast *ast, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (ast->right)
	{
		minishell->pipe_check = 1;
		ft_executer(ast->right, minishell);
	}
	dup2(ast->token->fd_0, STDIN_FILENO);
	dup2(ast->token->fd_1, STDOUT_FILENO);
	ft_pipe_redirection(minishell);
	while (i < minishell->pipe_num)
		close(minishell->store_fds[i++]);
	if (ast->type != N_COMMAND && ast->type != N_BUILTIN)
	{
		minishell->pipe_check = 1;
		ft_executer(ast, minishell);
		exit(0);
	}
	ft_simple_command2(ast, minishell);
}

void	ft_pipe_child_left(t_ast *ast, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (ast->right)
	{
		minishell->pipe_check = 1;
		ft_executer(ast->right, minishell);
	}
	dup2(ast->token->fd_1, STDOUT_FILENO);
	ft_pipe_redirection(minishell);
	while (i < minishell->pipe_num)
		close(minishell->store_fds[i++]);
	if (ast->type != N_COMMAND && ast->type != N_BUILTIN)
	{
		minishell->pipe_check = 1;
		ft_executer(ast, minishell);
		exit(0);
	}
	ft_simple_command2(ast, minishell);
}

void	ft_pipe_child_right(t_ast *ast, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (ast->right)
	{
		minishell->pipe_check = 1;
		ft_executer(ast->right, minishell);
	}
	dup2(ast->token->fd_0, STDIN_FILENO);
	ft_pipe_redirection(minishell);
	while (i < minishell->pipe_num)
		close(minishell->store_fds[i++]);
	if (ast->type != N_COMMAND && ast->type != N_BUILTIN)
	{
		minishell->pipe_check = 1;
		ft_executer(ast, minishell);
		exit(0);
	}
	ft_simple_command2(ast, minishell);
}

void	ft_pipeline(t_ast *ast, t_minishell *minishell, int flag)
{
	pid_t	pid_left;
	int		status;

	status = 0;
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
			status = ft_more_pipes(ast, minishell, 1);
		else
			status = ft_pipeline_aux(ast, minishell, flag);
	}
	minishell->status = WEXITSTATUS(status);
}
