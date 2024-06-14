/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:29:35 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/14 14:01:02 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	**ft_get_path(char **envp)
{
	int		i;
	int		flag;
	char	*str;
	char	**split;

	i = 0;
	flag = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
	{
		i++;
		if (envp[i] && ft_strncmp(envp[i], "PATH=", 5) == 0)
			flag = 1;
	}
	if (flag == 0)
		return (NULL);
	str = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	split = ft_split(str, ':');
	free(str);
	return (split);
}

void	expand_builtin(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->type == N_IDENTIFIER && check_builtin(ast->token->value))
		ast->type = N_BUILTIN;
	expand_builtin(ast->left);
	expand_builtin(ast->right);
}

void	expand_command(t_ast *ast, t_ast *prev, int flag)
{
	if (ast == NULL)
		return ;
	if (ft_strcmp(ast->token->value, "") == 0)
		return ;
	if (ast->type == N_IDENTIFIER && flag == 0
		&& !check_builtin(ast->token->value))
		ast->type = N_COMMAND;
	if (prev != NULL)
	{
		if (ast->type != N_REDIRECTION && ast->type != N_HEREDOC
			&& ast->type != N_PIPELINE)
		{
			if (check_prev(prev) && ast->type != N_ASSIGN
				&& flag == 1 && !check_builtin(ast->token->value))
				ast->type = N_COMMAND;
			else if (check_prev2(prev) && !check_builtin(ast->token->value) && ast->type != N_ASSIGN)
				ast->type = N_ARGUMENT;
		}
	}
	if (ast->type != N_REDIRECTION && ast->type != N_HEREDOC)
		expand_command(ast->left, ast, 1);
	else
		expand_command(ast->left, ast, 0);
	expand_command(ast->right, ast, 1);
}

void	expand_command2(t_ast *ast)
{
	char	*str;

	if (ast == NULL)
		return ;
	if (ft_expanser_directory(ast))
		ast->type = N_DIRECTORY;
	printf ("ast->type: %d\n", ast->type);
	if (ast->type == N_COMMAND && ast->token->value[0] != '.'
		&& ast->token->value[0] != '/')
	{
		str = ft_strjoin("/", ast->token->value);
		free(ast->token->value);
		ast->token->value = str;
	}
	expand_command2(ast->left);
	expand_command2(ast->right);
}

void	expand_command_3(t_ast *ast, char **path)
{
	int		i;
	char	*str;

	i = 0;
	if (!ast)
		return ;
	if (ast->type == N_COMMAND)
	{
		while (path[i] != NULL)
		{
			str = ft_strjoin(path[i], ast->token->value);
			if (access(str, F_OK | X_OK) == 0)
			{
				free(ast->token->value);
				ast->token->value = str;
				break ;
			}	
			free(str);
			str = NULL;
			i++;
		}
	}
	expand_command_3(ast->left, path);
	expand_command_3(ast->right, path);
}
