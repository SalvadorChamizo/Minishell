/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:17:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/08 19:23:02 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	ft_open_infile(t_ast *ast)
{
	int	fd;

	if (!check_files(ast))
	{
		fd = open(ast->token->value, O_RDONLY);
		if (fd < 0)
		{
			perror("open");
		}
		dup2(fd, STDIN_FILENO);
	}
}

void	ft_open_outfile(t_ast *ast)
{
	int	fd;

	if (access(ast->token->value, F_OK) != 0)
	{
		fd = open(ast->token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open");
		}
		dup2(fd, STDOUT_FILENO);
	}
	else
	{
		fd = open(ast->token->value, O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open");
		}
		dup2(fd, STDOUT_FILENO);
	}
}

void	ft_open_outfile_2(t_ast *ast)
{
	int	fd;

	if (access(ast->token->value, F_OK) != 0)
	{
		fd = open(ast->token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("open");
		}
		dup2(fd, STDOUT_FILENO);
	}
	else
	{
		fd = open(ast->token->value, O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("open");
		}
		dup2(fd, STDOUT_FILENO);
	}
}

void	ft_open_heredoc(t_ast *ast)
{
	int		fd;
	char	*buffer;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		manage_error("open");
	while (1)
	{
		ft_printf("> ");
		buffer = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(ast->left->token->value, buffer, ft_strlen(ast->left->token->value))
			&& ft_strlen(buffer) - 1 == ft_strlen(ast->left->token->value))
			break ;
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
	{
		unlink(".heredoc_tmp");
		manage_error("open");
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	ft_redirect(t_ast *ast, t_minishell *minishell)
{
	if (ast->right)
		ft_executer(ast->right, minishell);
	if (ft_strcmp(ast->token->value, "<") == 0)
		ft_open_infile(ast->left);
	else if (ft_strcmp(ast->token->value, ">") == 0)
		ft_open_outfile(ast->left);
	else if (ft_strcmp(ast->token->value, ">>") == 0)
		ft_open_outfile_2(ast->left);
	else if (ft_strcmp(ast->token->value, "<<") == 0)
		ft_open_heredoc(ast);
}
