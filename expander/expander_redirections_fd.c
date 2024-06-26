/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_redirections_fd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:35:18 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/26 13:08:34 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	expand_redir(t_ast *ast, t_ast *prev, int flag)
{
	if (ast == NULL)
		return ;
	if (prev != NULL)
	{
		if (prev->type == N_REDIRECTION && flag == 1
			&& (ast->type != N_REDIRECTION && ast->type != N_HEREDOC))
			ast->type = N_FILE;
		else if (prev->type == N_HEREDOC && flag == 1
			&& (ast->type != N_REDIRECTION && ast->type != N_HEREDOC))
			ast->type = N_DELIMITER;
	}
	expand_redir(ast->left, ast, 1);
	expand_redir(ast->right, ast, 0);
	return ;
}

int	count_pipes(t_ast *ast)
{
	int	i;

	i = 0;
	if (ast == NULL)
		return (0);
	while (ast->type == N_PIPELINE)
	{
		i++;
		ast = ast->right;
	}
	return (i);
}

void	ft_store_fds(t_ast *ast, t_minishell *minishell)
{
	int	i;
	int	*stored;

	i = 0;
	if (!ast || ast->type != N_PIPELINE)
		return ;
	minishell->pipe_num = count_pipes(ast) * 2;
	stored = malloc(sizeof(int) * minishell->pipe_num);
	while (ast->type == N_PIPELINE)
	{
		stored[i] = ast->token->pipefd[0];
		i++;
		stored[i] = ast->token->pipefd[1];
		i++;
		ast = ast->right;
	}
	minishell->store_fds = stored;
}

void	expand_pipefd(t_ast *ast, int flag)
{
	if (ast == NULL)
		return ;
	if (ast->type == N_PIPELINE && ast->right->type == N_PIPELINE)
	{
		pipe(ast->token->pipefd);
		ast->left->token->fd_1 = ast->token->pipefd[1];
		if (flag == 0)
			ast->left->token->fd_0 = ast->token->pipefd[0];
		if (ast->right->left->type == N_COMMAND
			|| ast->right->left->type == N_BUILTIN)
			ast->right->left->token->fd_0 = ast->token->pipefd[0];
	}
	else if (ast->type == N_PIPELINE
		&& (ast->right->type == N_COMMAND || ast->right->type == N_BUILTIN))
	{
		pipe(ast->token->pipefd);
		ast->left->token->fd_1 = ast->token->pipefd[1];
		if (flag == 0)
			ast->left->token->fd_0 = ast->token->pipefd[0];
		ast->right->token->fd_0 = ast->token->pipefd[0];
		ast->right->token->fd_1 = ast->token->pipefd[1];
	}
	if (ast->type == N_PIPELINE)
		expand_pipefd(ast->right, 1);
}
