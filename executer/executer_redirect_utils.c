/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirect_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:17:43 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/10 09:59:30 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	ft_open_outfile_aux(t_ast *ast, t_minishell *minishell)
{
	int	fd;

	if (!check_files_outfile(ast, minishell))
	{
		fd = open(ast->token->value, O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			perror("open");
		if (minishell->outfile_check == -1)
		{
			dup2(fd, STDOUT_FILENO);
			minishell->outfile_check = 1;
			minishell->fd_out_redir = fd;
		}
	}
}

void	ft_open_outfile_2_aux(t_ast *ast, t_minishell *minishell)
{
	int	fd;

	if (!check_files_outfile(ast, minishell))
	{
		fd = open(ast->token->value, O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			perror("open");
		if (minishell->outfile_check == -1)
		{
			dup2(fd, STDOUT_FILENO);
			minishell->outfile_check = 1;
			minishell->fd_out_redir = fd;
		}
	}
}

int	check_files_outfile(t_ast *ast, t_minishell *minishell)
{
	if (access(ast->token->value, W_OK) != 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(ast->token->value, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		if (minishell->pipe_check == 1)
			exit (1);
		else
			minishell->status = 1;
		return (1);
	}
	return (0);
}
