/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:46:49 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/11 11:20:00 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	write_heredoc_exit(char *buffer, int line_number)
{
	free(buffer);
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putnbr_fd(line_number, 2);
	ft_putstr_fd(" delimited by end of file\n", 2);
	exit (0);
}

void	reopen_heredoc(t_minishell *minishell, char *name)
{
	minishell->fd_in_redir = open(name, O_RDONLY);
	if (minishell->fd_in_redir < 0)
	{
		unlink(name);
		manage_error("open");
	}
}

void	ft_write_heredoc(t_ast *ast, t_minishell *minishell, char *name)
{
	char	*buffer;
	char	*delimiter;
	int		fd;

	delimiter = ast->left->token->value;
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	heredoc_signal();
	if (fd < 0)
		manage_error("open");
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL && isatty(STDIN_FILENO))
			write_heredoc_exit(buffer, minishell->line_number);
		if (!ft_strcmp(delimiter, buffer))
			break ;
		if (ft_check_dollar(buffer))
			buffer = ft_expand_heredoc(buffer, minishell);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	close(fd);
	reopen_heredoc(minishell, name);
	signal(SIGINT, sigint_signal);
}

void	store_heredoc_aux(t_ast *ast, t_minishell *mnshll, char *name, int pid)
{
	int	status;

	g_command_sig = pid;
	if (!pid)
	{
		ft_write_heredoc(ast, mnshll, name);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		mnshll->fd_in_redir = open(name, O_RDONLY);
		if (mnshll->fd_in_redir < 0)
		{
			unlink(name);
			manage_error("open");
		}
		mnshll->status = status;
		free(name);
	}
}

int	ft_store_heredoc(t_ast *ast, t_minishell *minishell, int num)
{
	char	*filename;
	char	*number;
	pid_t	pid;

	if (!ast)
		return (num);
	if (ast->type == N_HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		number = ft_itoa(num);
		filename = ft_strjoin(".heredoc_tmp", number);
		free(number);
		pid = fork();
		store_heredoc_aux(ast, minishell, filename, pid);
		num++;
		signal(SIGQUIT, quit_signal);
		signal(SIGINT, sigint_signal);
	}
	num = ft_store_heredoc(ast->left, minishell, num);
	num = ft_store_heredoc(ast->right, minishell, num);
	return (num);
}
