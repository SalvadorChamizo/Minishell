/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:11:31 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/22 15:55:11 by saroca-f         ###   ########.fr       */
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

/*void	expand_quotes2(t_ast *ast)
{
	t_ast	*temp;
	t_ast	*prev;
	char	*str1;
	char	*str2;
	char	*str3;

	if (ast == NULL)
		return ;
	temp = ast;
	prev = temp;
	while (temp)
	{
		if ()
		temp = temp->left;
	}
	expand_quotes2(ast->right);
}*/

void	expand_quotes(t_ast *ast)
{
	char	*str;

	if (ast == NULL)
		return ;
	if (ast->token->value[0] == '\"' || ast->token->value[0] == '\'')
	{
		ast->token->quote = 1;
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
		if (!ast->token || ft_strcmp(ast->token->value, "") == 0)
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
	int *stored;

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

void	ft_heredoc_store(t_ast *ast, t_minishell *minishell, char *file)
{
	char	*buffer;
	char	*delimiter;
	int		fd;

	delimiter = ast->left->token->value;
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
			exit(0);
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
	exit(0);
}

void	ft_store_heredoc(t_ast *ast, t_minishell *minishell, int num)
{
	char	*filename;
	char	*number;
	pid_t	pid;

	if (!ast)
		return ;
	if (ast->type == N_HEREDOC)
	{
		signal(SIGINT, ft_heredoc_sigint_handler);
		number = ft_itoa(num);
		filename = ft_strjoin(".heredoc_tmp", number);
		num++;
		pid = fork();
		g_command_sig = pid;
		if (!pid)
			ft_heredoc_store(ast, minishell, filename);
		waitpid(pid, NULL, 0);
		minishell->fd_in_redir = open(filename, O_RDONLY);
		if (minishell->fd_in_redir < 0)
		{
			unlink(filename);
			manage_error("open");
		}
		free(filename);
		free(number);
		signal(SIGINT, sigint_signal);
	}
	ft_store_heredoc(ast->left, minishell, num);
	ft_store_heredoc(ast->right, minishell, num);
}

void	ft_expanser(t_minishell *minishell, char **envp)
{
	t_ast			*ast;
	char			**path;

	ast = minishell->ast;
	path = ft_get_path(envp);
	remove_empty_node(ast, NULL);
	if (!ast || !ast->token)
	{
		minishell->ast = NULL;
		return ;
	}
	expand_redir(ast, NULL, 0);
	ft_dollar(ast, minishell->list, minishell);
	expand_quotes(ast);
	//expand_quotes2(ast);
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
