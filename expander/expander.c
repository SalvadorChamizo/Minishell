/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:11:31 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/09 17:37:50 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

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

int	check_assign_aux(t_ast *ast, char **env, int j, int i)
{
	if (!ft_strncmp(env[j], ast->token->value, i))
	{
		free(env[j]);
		env[j] = ft_strdup(ast->token->value);
		return (1);
	}
	return (0);
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
			if (check_assign_aux(ast, env, j, i) == 1)
				return (1);
			j++;
		}
	}
	check_assign_env(ast->left, env);
	check_assign_env(ast->right, env);
	return (0);
}

void	ft_expander(t_minishell *minishell, char **envp)
{
	t_ast	*ast;
	char	**path;

	ast = minishell->ast;
	path = ft_get_path(envp);
	remove_empty_node(ast, NULL);
	expand_redir(ast, NULL, 0);
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
}
