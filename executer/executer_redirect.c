/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:17:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/14 18:30:50 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	ft_open_infile(t_ast *ast, t_minishell *minishell)
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
		if (minishell->pipe_check)
		{
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
		dup2(fd, STDOUT_FILENO);
		if (minishell->pipe_check)
		{
			minishell->outfile_check = 1;
			minishell->fd_out_redir = fd;
		}
	}
	else
	{
		fd = open(ast->token->value, O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open");
		}
		dup2(fd, STDOUT_FILENO);
		if (minishell->pipe_check)
		{
			minishell->outfile_check = 1;
			minishell->fd_out_redir = fd;
		}
	}
}

void	ft_open_outfile_2(t_ast *ast, t_minishell *minishell)
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
		if (minishell->pipe_check)
		{
			minishell->outfile_check = 1;
			minishell->fd_out_redir = fd;
		}
	}
	else
	{
		fd = open(ast->token->value, O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("open");
		}
		dup2(fd, STDOUT_FILENO);
		if (minishell->pipe_check)
		{
			minishell->outfile_check = 1;
			minishell->fd_out_redir = fd;
		}
	}
}

void	ft_heredoc_pipe(t_ast *ast, t_minishell *minishell)
{
	char	*buffer;
	char	*delimiter;
	int		fd;

	delimiter = ast->left->token->value;
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		manage_error("open");
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL && isatty(STDIN_FILENO))
		{
			free(buffer);
			ft_putstr_fd("bash: warning: here-document at line ", 2);
			ft_putnbr_fd(minishell->line_number, 2);
			ft_putstr_fd(" delimited by end of file\n", 2);
			exit (0);
		}
		if (!ft_strcmp(delimiter, buffer))
			break ;
		if (ft_check_dollar(buffer))
			buffer = ft_expand_heredoc(buffer, minishell);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	close(fd);
	minishell->fd_in_redir = open(".heredoc_tmp", O_RDONLY);
	if (minishell->fd_in_redir < 0)
	{
		unlink(".heredoc_tmp");
		manage_error("open");
	}
}

void	ft_child_heredoc(t_ast *ast, t_minishell *minishell, int pipe_doc[2])
{
	char	*buffer;
	char	*delimiter;

	delimiter = ast->left->token->value;
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL && isatty(STDIN_FILENO))
		{
			free(buffer);
			ft_putstr_fd("bash: warning: here-document at line ", 2);
			ft_putnbr_fd(minishell->line_number, 2);
			ft_putstr_fd(" delimited by end of file\n", 2);
			exit (0);
		}
		if (!ft_strcmp(delimiter, buffer))
			break ;
		if (ft_check_dollar(buffer))
			buffer = ft_expand_heredoc(buffer, minishell);
		write(pipe_doc[1], buffer, ft_strlen(buffer));
		write(pipe_doc[1], "\n", 1);
		free(buffer);
	}
	free(buffer);
	close(pipe_doc[1]);
	exit(0);	
}

void	ft_open_heredoc(t_ast *ast, t_minishell *minishell)
{
	char	*buffer;
	pid_t	pid;
	int		pipe_doc[2];

	buffer = NULL;
	signal(SIGINT, ft_heredoc_sigint_handler);
	if (minishell->pipe_check != 1)
	{
		pipe(pipe_doc);
		pid = fork();
		g_command_sig = pid;
		if (!pid)
		{
			close(pipe_doc[0]);
			ft_child_heredoc(ast, minishell, pipe_doc);
		}
		waitpid(pid, NULL, 0);
		dup2(pipe_doc[0], STDIN_FILENO);
		close(pipe_doc[0]);
		close(pipe_doc[1]);
	}
	else
	{
		ft_heredoc_pipe(ast, minishell);
		minishell->infile_check = 1;
		minishell->heredoc_check = 1;
	}

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
		ft_open_heredoc(ast, minishell);
		signal(SIGINT, sigint_signal);
	}
}
