/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:17:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/10 10:14:41 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	ft_open_infile(t_ast *ast, t_minishell *minishell)
{
	int	fd;

	if (!check_files(ast, minishell))
	{
		fd = open(ast->token->value, O_RDONLY);
		if (fd < 0)
			perror("open");
		if (minishell->infile_check == -1)
		{
			dup2(fd, STDIN_FILENO);
			minishell->infile_check = 1;
			minishell->fd_in_redir = fd;
		}
	}
}

void	ft_open_outfile(t_ast *ast, t_minishell *minishell)
{
	int	fd;

	if (access(ast->token->value, F_OK) != 0)
	{
		fd = open(ast->token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open");
		}
		if (minishell->outfile_check == -1)
		{
			dup2(fd, STDOUT_FILENO);
			minishell->outfile_check = 1;
			minishell->fd_out_redir = fd;
		}
	}
	else
		ft_open_outfile_aux(ast, minishell);
}

void	ft_open_outfile_2(t_ast *ast, t_minishell *minishell)
{
	int	fd;

	if (access(ast->token->value, F_OK) != 0)
	{
		fd = open(ast->token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			perror("open");
		if (minishell->outfile_check == -1)
		{
			dup2(fd, STDOUT_FILENO);
			minishell->outfile_check = 1;
			minishell->fd_out_redir = fd;
		}
	}
	else
		ft_open_outfile_2_aux(ast, minishell);
}

void	ft_redirect(t_ast *ast, t_minishell *minishell)
{
	if (ast->right)
		ft_executer(ast->right, minishell);
	if (ft_strcmp(ast->token->value, "<") == 0)
		ft_open_infile(ast->left, minishell);
	else if (ft_strcmp(ast->token->value, ">") == 0)
		ft_open_outfile(ast->left, minishell);
	else if (ft_strcmp(ast->token->value, ">>") == 0)
		ft_open_outfile_2(ast->left, minishell);
	else if (ft_strcmp(ast->token->value, "<<") == 0)
	{
		if (minishell->infile_check == -1)
		{
			minishell->infile_check = 1;
			dup2(minishell->fd_in_redir, STDIN_FILENO);
		}
	}
}
