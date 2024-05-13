/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:19:00 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/13 15:38:07 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	expand_builtin(t_syntax *ast)
{
	if (ast == NULL)
		return ;
	if (ast->token->type == T_COMMAND && check_builtin(ast->token->value))
		ast->token->type = T_BUILTIN;
	expand_builtin(ast->left);
	expand_builtin(ast->right);
}

void	expand_command(t_syntax *tree)
{
	if (tree == NULL)
		return ;
	if (tree->token->type == T_IDENTIFIER)
	{
		tree->token->type = T_COMMAND;
		return ;
	}
	else if (tree->token->type == T_ASS)
		expand_command(tree->left);
	else if (tree->token->type == T_PIPE)
	{
		if (tree->right != NULL)
			expand_command(tree->right);
		if (tree->left != NULL)
			expand_command(tree->left);
	}
}

void	expand_redir(t_syntax *tree)
{
	if (tree == NULL)
		return ;
	if (tree->token->type != T_PIPE && tree->token->type != T_IDENTIFIER)
	{
		printf(RED"No hay problema 2\n");
		if (tree->token->type != T_DLESS && tree->left)
		{
			printf(RED"ENTRO\n");
			tree->left->token->type = T_FILE;
			printf(RED"SALIO\n");
		}
		else if (tree->token->type == T_DLESS && tree->left)
		{
			printf(RED"ENTRO\n");
			tree->left->token->type = T_DELIMITER;
			printf(RED"SALIO\n");
		}
		printf(RED"No hay problema 2,5\n");
		expand_redir(tree->right);
		printf(RED"No hay problema 3\n");
	}
	else
	{
		if (tree->right != NULL)
			expand_redir(tree->right);
		if (tree->left != NULL)
			expand_redir(tree->left);
	}
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

void	expand_assignment(t_syntax *ast)
{
	if (ast == NULL)
		return ;
	if (check_equal(ast->token->value) && ast->token->type != T_SQUOTE
		&& ast->token->type != T_DQUOTE)
		ast->token->type = T_ASS;
	if (ast->token->type == T_PIPE)
	expand_assignment(ast->left);
	expand_assignment(ast->right);
}

/*t_assign_list	*new_assignment(char *text)
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

void	store_assignment(t_syntax *tree, t_assign_list **list)
{
	t_assign_list	*new_node;

	new_node = NULL;
	if (tree == NULL)
		return ;
	if (tree->type == T_ASS)
	{
		new_node = new_assignment(tree->token->value);
		ft_assign_add_back(list, new_node);
	}
	store_assignment(tree->left, list);
	store_assignment(tree->right, list);
}*/

void	ft_expanser(t_syntax *tree)
{
	t_syntax		*tree_temp;
	//t_assign_list	*list;

	//list = NULL;
	tree_temp = tree;
	expand_redir(tree_temp);
	//expand_assignment(tree);
	expand_command(tree);
	expand_builtin(tree);
	/*expand_command2(tree);
	print_ast(tree);
	store_assignment(tree, &list);
	print_assignment(tree);*/
}
