/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:11:31 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/10 11:49:14 by schamizo         ###   ########.fr       */
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
	if (ast->type == N_ASSIGN)
	{
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

void	ft_expanser(t_minishell *minishell, char **envp)
{
	t_ast			*ast;
	char			**path;

	ast = minishell->ast;
	path = ft_get_path(envp);
	remove_empty_node(ast, NULL);
	expand_redir(ast, NULL, 0);
	ft_dollar(ast, minishell->list, minishell);
	expand_quotes(ast);
	expand_assignment(ast, NULL);
	expand_command(ast, NULL, 0);
	expand_builtin(ast);
	expand_command2(ast);
	if (!path)
		return ;
	expand_command_3(ast, path);
	check_assign_env(ast, minishell->env);
	store_assignment(ast, &minishell->list);
	free_split(path);
	//print_assignment(minishell->list);
}
