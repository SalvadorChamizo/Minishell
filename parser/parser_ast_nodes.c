/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:11:29 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/17 19:38:40 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

t_nodetype	return_type(t_token *token)
{
	if (token->type == T_IDENTIFIER)
		return (N_IDENTIFIER);
	else if (token->type == T_DLESS)
		return (N_HEREDOC);
	else if (is_redirection(token))
		return (N_REDIRECTION);
	else if (token->type == T_PIPE)
		return (N_PIPELINE);
	else
		return (N_IDENTIFIER);
}

t_ast	*new_i_node(t_token *token)
{
	t_ast	*ast_node;

	ast_node = malloc(sizeof(t_ast));
	ast_node->type = return_type(token);
	ast_node->token = token;
	ast_node->left = NULL;
	ast_node->right = NULL;
	return (ast_node);
}

t_ast	*iden_node(t_idenlst *lst)
{
	t_ast	*ast_node;

	ast_node = NULL;
	if (lst->next != NULL)
	{
		ast_node = iden_node(lst->next);
	}
	ast_node = new_b_node(ast_node, lst->token, NULL);
	return (ast_node);
}

t_ast	*new_b_node(t_ast *left, t_token *op, t_ast *right)
{
	t_ast	*ast_node;

	ast_node = malloc(sizeof(t_ast));
	ast_node->type = return_type(op);
	ast_node->token = op;
	ast_node->left = left;
	ast_node->right = right;
	return (ast_node);
}

t_ast	*new_b_node2(t_ast *left, t_token *op, t_ast *right, t_ast *iden)
{
	t_ast	*ast_node;

	ast_node = malloc(sizeof(t_ast));
	ast_node->type = return_type(op);
	ast_node->token = op;
	ast_node->left = left;
	ast_node->right = iden;
	iden->right = right;
	return (ast_node);
}
