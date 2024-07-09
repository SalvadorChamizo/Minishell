/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:11:31 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/08 20:06:20 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	expand_quotes(t_ast *ast)
{
	char	*str;

	if (ast == NULL)
		return ;
	if (ast->token->value[0] == '\"' || ast->token->value[0] == '\'')
	{
		if (ast->token->value[0] == '\"')
		{
			str = ft_strtrim(ast->token->value, "\"");
			free(ast->token->value);
			ast->token->value = str;
		}
		else if (ast->token->value[0] == '\'')
		{
			str = ft_strtrim(ast->token->value, "\'");
			free(ast->token->value);
			ast->token->value = str;
		}
	}
	expand_quotes(ast->left);
	expand_quotes(ast->right);
}

void	remove_empty_node(t_ast *ast, t_ast *prev)
{
	if (!ast)
		return ;
	if (!ast->left && !ast->right)
	{
		if (ft_strcmp(ast->token->value, "") == 0)
		{
			free(ast->token->value);
			free(ast->token);
			free(ast);
			if (prev)
				prev->left = NULL;
			return ;
		}
	}
	remove_empty_node(ast->left, ast);
	remove_empty_node(ast->right, ast);
}

int	check_assign_env(t_ast *ast, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!ast)
		return (0);
	if (ast->type == N_ASSIGN || ast->type == N_ARGUMENT)
	{
		if (check_equal(ast->token->value) == 0)
			return (0);
		while (ast->token->value[i] != '=')
			i++;
		while (env[j])
		{
			if (!ft_strncmp(env[j], ast->token->value, i))
			{
				free(env[j]);
				env[j] = ft_strdup(ast->token->value);
				return (1);
			}
			j++;
		}
	}
	check_assign_env(ast->left, env);
	check_assign_env(ast->right, env);
	return (0);
}

void	ft_write_heredoc(t_ast *ast, t_minishell *minishell, char *name)
{
	char	*buffer;
	char	*delimiter;
	int		fd;

	delimiter = ast->left->token->value;
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	heredoc_signal();
	//signal(SIGINT, SIG_IGN);
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
	minishell->fd_in_redir = open(name, O_RDONLY);
	if (minishell->fd_in_redir < 0)
	{
		unlink(name);
		manage_error("open");
	}
	signal(SIGINT, sigint_signal);
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
		pid = fork();
		g_command_sig = pid;
		if (!pid)
			ft_write_heredoc(ast, minishell, filename);
		else
		{
			waitpid(pid, NULL, 0);
			minishell->fd_in_redir = open(filename, O_RDONLY);
			if (minishell->fd_in_redir < 0)
			{
				unlink(filename);
				manage_error("open");
			}
			free(filename);
			free(number);
			num++;
		}
		signal(SIGQUIT, quit_signal);
		signal(SIGINT, sigint_signal);
	}
	num = ft_store_heredoc(ast->left, minishell, num);
	num = ft_store_heredoc(ast->right, minishell, num);
	return (num);
}

void	ft_expanser(t_minishell *minishell, char **envp)
{
	t_ast	*ast;
	char	**path;

	ast = minishell->ast;
	path = ft_get_path(envp);
	remove_empty_node(ast, NULL);
	expand_redir(ast, NULL, 0);
	//ft_dollar(ast, minishell->list, minishell);
	expand_quotes(ast);
	expand_assignment(ast, NULL);
	expand_command(ast, NULL, 0);
	expand_builtin(ast);
	expand_command2(ast);
	if (!path)
		return ;
	expand_command_3(ast, path);
	expand_pipefd(ast, 0);
	ft_store_fds(ast, minishell);
	ft_store_heredoc(ast, minishell, 1);
	check_assign_env(ast, minishell->env);
	store_assignment(ast, &minishell->list);
	free_split(path);
	//print_assignment(minishell->list);
}
