/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:11:31 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/23 18:52:16 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	check_builtin(char *text)
{
	if (!ft_strcmp(text, "echo"))
		return (1);
	else if (!ft_strcmp(text, "cd"))
		return (1);
	else if (!ft_strcmp(text, "pwd"))
		return (1);
	else if (!ft_strcmp(text, "export"))
		return (1);
	else if (!ft_strcmp(text, "unset"))
		return (1);
	else if (!ft_strcmp(text, "env"))
		return (1);
	else if (!ft_strcmp(text, "exit"))
		return (1);
	return (0);
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

void	expand_command2(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->type == N_COMMAND)
		ast->token->value = ft_strjoin("/", ast->token->value);
	expand_command2(ast->left);
	expand_command2(ast->right);
}

int	check_prev(t_ast *prev)
{
	if (prev->type != N_IDENTIFIER && prev->type != N_COMMAND
		&& prev->type != N_ARGUMENT)
		return (1);
	return (0);
}

int	check_prev2(t_ast *prev)
{
	if (prev->type == N_IDENTIFIER || prev->type == N_COMMAND
		|| prev->type == N_ARGUMENT)
		return (1);
	return (0);
}

void	expand_command(t_ast *ast, t_ast *prev, int flag)
{
	if (ast == NULL)
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

int	check_equal(char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i] == '=' && i != 0)
			return (1);
		i++;
	}
	return (0);
}

void	expand_assignment(t_ast *ast, t_ast *prev)
{
	if (ast == NULL)
		return ;
	if (prev == NULL && check_equal(ast->token->value))
		ast->type = N_ASSIGN;
	if (prev != NULL)
	{
		if (prev->type != N_COMMAND && prev->type != N_IDENTIFIER
			&& prev->type != N_ARGUMENT && check_equal(ast->token->value))
			ast->type = N_ASSIGN;
	}
	expand_assignment(ast->left, ast);
	expand_assignment(ast->right, ast);
}

t_assign_list	*new_assignment(char *text)
{
	t_assign_list	*new_node;
	int				i;

	i = 0;
	new_node = malloc(sizeof(t_assign_list));
	while (text[i] != '=')
		i++;
	new_node->variable = ft_substr(text, 0, i);
	new_node->value = ft_substr(text, i + 1, ft_strlen(text) - i);
	new_node->next = NULL;
	return (new_node);
}

void	ft_assign_add_back(t_assign_list **lst, t_assign_list *new)
{
	t_assign_list	*last;

	last = *lst;
	if (!last)
		*lst = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	store_assignment(t_ast *ast, t_assign_list **list)
{
	t_assign_list	*new_node;

	new_node = NULL;
	if (ast == NULL)
		return ;
	if (ast->type == N_ASSIGN)
	{
		new_node = new_assignment(ast->token->value);
		ft_assign_add_back(list, new_node);
	}
	store_assignment(ast->left, list);
	store_assignment(ast->right, list);
}

void	ft_expanser(t_ast *ast)
{
	t_ast			*ast_temp;
	t_assign_list	*list;

	list = NULL;
	ast_temp = ast;
	expand_redir(ast, NULL, 0);
	expand_assignment(ast, NULL);
	expand_command(ast, NULL, 0);
	expand_builtin(ast);
	expand_command2(ast);
	//print_ast(ast);
	store_assignment(ast, &list);
	print_assignment(list);
}
