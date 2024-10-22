/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:29:35 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/11 11:33:01 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

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
			else if (check_prev2(prev)
				&& !check_builtin(ast->token->value) && ast->type != N_ASSIGN)
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

	str = NULL;
	if (ast == NULL)
		return ;
	if (ft_expanser_directory(ast))
		ast->type = N_DIRECTORY;
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

void	expand_command_3_aux(t_ast *ast, t_ast *temp, char **path)
{
	int		i;
	char	*str;

	i = 0;
	if (ast->type == N_COMMAND)
	{
		ast->token->value = command_args_builder(&temp, 1);
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
}

void	expand_command_3(t_ast *ast, char **path)
{
	t_ast	*temp;

	temp = ast;
	if (!ast)
		return ;
	expand_command_3_aux(ast, temp, path);
	expand_command_3(ast->left, path);
	expand_command_3(ast->right, path);
}
