/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:10:25 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/17 19:39:53 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	print_ast_helper(t_ast *node, int depth, char *side)
{
	if (node == NULL)
		return ;
	if (node->type == N_IDENTIFIER)
	{
		printf(RED"%*s%s"RESET""YELLOW"IDENTIFIER:"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_REDIRECTION)
	{
		printf(RED"%*s%s"RESET""YELLOW"REDIRECTION:"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_COMMAND)
	{
		printf(RED"%*s%s"RESET""YELLOW"COMMAND:"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_ASSIGN)
	{
		printf(RED"%*s%s"RESET""YELLOW"ASSIGNMENT:"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_BUILTIN)
	{
		printf(RED"%*s%s"RESET""YELLOW"BUILTIN:"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_ARGUMENT)
	{
		printf(RED"%*s%s"RESET""YELLOW"ARGUMENT:"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_DELIMITER)
	{
		printf(RED"%*s%s"RESET""YELLOW"LIMITER:"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_FILE)
	{
		printf(RED"%*s%s"RESET""YELLOW"FILE:"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->type == N_HEREDOC)
	{
		printf(RED"%*s%s"RESET""YELLOW"HEREDOC:"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else
	{
		printf(RED"%*s%s"RESET""YELLOW"PIPELINE:"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
}

void	print_ast(t_ast *root)
{
	printf(GREEN"ARBOL\n");
	print_ast_helper(root, 0, "root: ");
}

void	print_assignment(t_assign_list *list)
{
	t_assign_list	*temp;
	int				i;

	i = 1;
	temp = list;
	if (!list)
		printf(BLUE"No assignments\n"RESET);
	else
	{
		printf(BLUE"\nAssignment List\n"RESET);
		while (temp)
		{
			printf("Node %d: Variable = %s, Value = %s\n", i, temp->variable, temp->value);
			temp = temp->next;
			i++;
		}		
	}
}

void	print_list(t_idenlst *list)
{
	t_idenlst	*temp;
	int			i;

	i = 1;
	temp = list;
	if (!list)
		printf(BLUE"No list\n"RESET);
	else
	{
		printf(BLUE"\nList\n"RESET);
		while (temp)
		{
			printf("Node %d: Value = %s\n", i, temp->token->value);
			temp = temp->next;
			i++;
		}		
	}
}