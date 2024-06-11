/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:17:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/11 11:29:37 by schamizo         ###   ########.fr       */
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

static void	ft_heredoc_sigint_handler(int signum)
{
	(void)signum;
	//ft_clean_ms();
	if (command_sig == 0)
	{
		write(1, "\n", 1);
		exit(SIGINT);
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
			printf("bash: warning: here-document at line ");
			printf("%d delimited by end of file\n", minishell->line_number);
		}
		if (!ft_strcmp(delimiter, buffer))
			break ;
		if (ft_check_dollar(buffer))
			buffer = ft_expand_heredoc(buffer, minishell);
		write(pipe_doc[1], buffer, ft_strlen(buffer));
		write(pipe_doc[1], "\n", 1);
	}
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
	pipe(pipe_doc);
	pid = fork();
	command_sig = pid;
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
	{
		ft_open_heredoc(ast, minishell);
		signal(SIGINT, sigint_signal);
	}
}
