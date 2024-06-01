/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:47:22 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/01 11:35:37 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	execute_builtin(t_ast *ast, char ***env, t_assign_list **list)
{
	if (!ft_strcmp(ast->token->value, "cd"))
		ft_cd(ast, *env);
	else if (!ft_strcmp(ast->token->value, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(ast->token->value, "echo"))
		ft_echo(ast);
	else if (!ft_strcmp(ast->token->value, "env"))
		ft_env(*env);
	else if (!ft_strcmp(ast->token->value, "export"))
		ft_export(ast, env, *list);
	else if (!ft_strcmp(ast->token->value, "unset"))
		ft_unset(ast, list);
}

char	**ft_command_args(t_ast *ast)
{
	t_ast	*temp;
	char	**args;
	int		i;

	temp = ast;
	i = 0;
	while (temp)
	{
		temp = temp->left;
		i++;
	}
	temp = ast;
	args = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (temp)
	{
		args[i] = temp->token->value;
		temp = temp->left;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	ft_simple_command(t_ast *ast, char ***env, t_assign_list **list)
{
	pid_t	pid;

	if (ast->right)
		ft_executer(ast->right, env, list);
	if (access(ast->token->value, F_OK | X_OK) != 0)
	{
		printf("Command \"%s\" not found\n", ast->token->value);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0
		&& execve(ast->token->value, ft_command_args(ast), *env) == -1)
	{
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
}

void	ft_command(t_ast *ast, char ***env, t_assign_list **list)
{
	pid_t	pid;
	t_ast	*temp;
	int		cont;
	int		i;

	cont = 0;
	i = 0;
	temp = ast;
	if (ast->right)
	{
		ft_executer(ast->right, env, list);
	}
	if (access(ast->token->value, F_OK | X_OK) != 0)
	{
		printf("Command \"%s\" not found\n", ast->token->value);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0
		&& execve(ast->token->value, ft_command_args(ast), *env) == -1)
	{
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
}

int	check_files(t_ast *ast)
{
	if (access(ast->token->value, F_OK) != 0)
	{
		printf("bash: %s: No such file or directory\n", ast->token->value);
		return (1);
	}
	if (access(ast->token->value, R_OK) != 0)
	{
		ft_printf("bash: %s: Permission denied\n", ast->token->value);
		return (1);
	}
	return (0);
}

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

void	ft_redirect(t_ast *ast, char ***env, t_assign_list **list)
{
	if (ast->right)
		ft_executer(ast->right, env, list);
	if (ft_strcmp(ast->token->value, "<") == 0)
		ft_open_infile(ast->left);
	else if (ft_strcmp(ast->token->value, ">") == 0)
		ft_open_outfile(ast->left);
	else if (ft_strcmp(ast->token->value, ">>") == 0)
		ft_open_outfile_2(ast->left);
	/*else if (ast->token->value == '<<')
		ft_open_heredoc(ast);*/
}

void	ft_pipeline(t_ast *ast, char ***env, t_assign_list **list)
{
	
	if (ast->type == N_PIPELINE)
	{
		ft_pipeline(ast->left, env, list);
		ft_pipeline(ast->right, env, list);
	}
	if (ast->type == N_HEREDOC || ast->type == N_REDIRECTION)
	{

	}
	if (ast->type == N_COMMAND)
	{
		ft_command(ast, env, list);
	}
	if (ast->type == N_BUILTIN)
	{
		execute_builtin(ast, env, list);
	}
}

void	ft_executer(t_ast *ast, char ***env, t_assign_list **list)
{
	if (!ast)
		return ;
	if (ast->type == N_PIPELINE)
	{
		ft_pipeline(ast->left, env, list);
		ft_pipeline(ast->right, env, list);
	}
	if (ast->type == N_BUILTIN)
	{
		execute_builtin(ast, env, list);
	}
	if (ast->type == N_COMMAND)
	{
		ft_simple_command(ast, env, list);
	}
	if (ast->type == N_REDIRECTION)
	{
		ft_redirect(ast, env, list);
	}
}