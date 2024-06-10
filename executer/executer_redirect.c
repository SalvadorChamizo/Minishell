/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:17:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/10 18:47:08 by schamizo         ###   ########.fr       */
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

char	*remove_dollar_heredoc(char	*str)
{
	char	*new_text;
	int		i;
	int		j;

	new_text = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			while (str[i] != ' ' && str[i] != '\0')
				i++;
		}
		new_text[j] = str[i];
		if (str[i] != '\0')
			i++;
		j++;
	}
	new_text[j] = '\0';
	free(str);
	return (new_text);
}

static void	ft_heredoc_sigint_handler(int signum)
{
	(void)signum;
	//ft_clean_ms();
	exit(SIGINT);
}

char	*heredoc_dollar_env(char *str, char **env, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	int				i;

	i = 0;
	dollar = malloc(sizeof(t_dollar));
	new_text = malloc(sizeof(char) * 2048);
	dollar->flag = flag;
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollar->variable = get_variable(str, &i);
			check_variable_env(env, dollar, new_text);
		}
		new_text[dollar->k++] = str[i++];
	}
	new_text[dollar->k] = '\0';
	flag = dollar->flag;
	free(dollar->variable);
	free(dollar);
	free(str);
	return (new_text);
}

char	*heredoc_dollar_list(char *str, t_assign *list, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	t_assign	*temp;
	int				i;

	i = 0;
	dollar = malloc(sizeof(t_dollar));
	new_text = malloc(sizeof(char) * 2048);
	dollar->flag = flag;
	if (!ft_check_dollar(str))
		return (str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollar->variable = get_variable(str, &i);
			temp = list;
			check_variable_copy2(temp, dollar, new_text);
		}
		new_text[dollar->k++] = str[i++];
	}
	free(dollar->variable);
	free(dollar);
	free(str);
	return (new_text);
}

char	*expand_status_heredoc(char *str, t_minishell *minishell)
{
	t_dollar	*dollar;
	int			i;
	char		*new_text;

	i = 0;
	dollar = malloc(sizeof(t_dollar));
	dollar->j = 0;
	dollar->k = 0;
	new_text = malloc(sizeof(char) * 2048);
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollar->variable = get_variable(str, &i);
			check_variable_copy(dollar, new_text, minishell, &i);
		}
		new_text[dollar->j++] = str[i++];
	}
	new_text[dollar->j] = '\0';
	free(str);
	free(dollar->variable);
	return (new_text);
}

char	*ft_expand_heredoc(char *str, t_minishell *minishell)
{
	int	flag;
	int	len;

	flag = 0;
	len = 0;
	if (!str)
		return (str);
	if (ft_check_dollar(str) && ft_strchr(str, '?'))
		str = expand_status_heredoc(str, minishell);
	if (ft_check_dollar(str))
	{
		if (!minishell->list)
			str = remove_dollar_heredoc(str);
		else if (minishell->list)
		{
			str = heredoc_dollar_env(str, minishell->env, &flag);
			str = heredoc_dollar_list(str, minishell->list, &flag);
			if (flag == 0)
				str = remove_dollar_heredoc(str);
		}
	}
	return (str);
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
	if (!pid)
	{
		close(pipe_doc[0]);
		while (1)
		{
			buffer = readline("> ");
			if (buffer == NULL && isatty(STDIN_FILENO))
				printf("bash: warning: here-document at line %d delimited by end-of-file\n", minishell->line_number);
			if (!ft_strcmp(ast->left->token->value, buffer))
				break ;
			if (ft_check_dollar(buffer))
				buffer = ft_expand_heredoc(buffer, minishell);
			write(pipe_doc[1], buffer, ft_strlen(buffer));
			write(pipe_doc[1], "\n", 1);
		}
		close(pipe_doc[1]);
		exit(0);
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
		ft_open_heredoc(ast, minishell);
}
