/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:11:29 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/17 11:49:10 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

/*t_astnode	*create_binop_node(t_astnode *left, t_token *op, t_astnode *right)
{
	t_astnode	*ast_node;

	ast_node = malloc(sizeof(t_astnode));
	ast_node->type = BINOP;
	ast_node->token = op;
	ast_node->left = left;
	ast_node->right = right;
	return (ast_node);
}*/

/*t_nodetype	return_type(t_token *token)
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

t_ast	*create_word_node(t_input *input, t_token *token)
{
	t_ast	*ast_node;

	ast_node = malloc(sizeof(t_ast));
	if (input->current_token->type == T_IDENTIFIER)
	{
		ast_node->type = type;
		ast_node->token = token;
		while (input->current_token->type == T_IDENTIFIER)
		{
			token = input->current_token;
			ft_eat(input, T_IDENTIFIER);
			ast_node->right = create_word_node(input, token, N_ARGUMENT, 0);
		}
	}
	else
	{
		ast_node->left = NULL;
		ast_node->right = NULL;
	}
	return (ast_node);
}*/

/*t_ast	*create_redirec_node(t_input *input, t_ast *root, t_token *token)
{
	t_ast	*ast_node;

	ast_node = malloc(sizeof(t_ast));
	ast_node->type = N_REDIRECTION;
	ast_node->token = token;
	if (input->current_token->type == T_IDENTIFIER)
	{
		token = input->current_token;
		ft_eat(input, T_IDENTIFIER);
		ast_node->left = create_word_node(input, token, N_ARGUMENT, 1);
		ast_node->right = NULL;
	}
	if (root != NULL)
	{
		root->left = ast_node;
		return (root);
	}
	return (ast_node);
}*/
