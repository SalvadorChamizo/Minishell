/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:15:24 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/09 15:45:43 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	eat(t_input *input, t_tokentype type)
{
	if (input->current_token->type == type)
		input->current_token = get_next_token(input);
	else
		exit(1);
}

t_syntax	*binap_nose(t_token *token, t_syntax *left, t_syntax *right)
{
	t_syntax	*new_node;

	new_node = malloc(sizeof(t_syntax));
	new_node->type = BINOP;
	new_node->token = token;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

t_syntax	*endap_nose(t_token *token)
{
	t_syntax	*new_node;

	new_node = malloc(sizeof(t_syntax));
	new_node->type = ENDOP;
	new_node->token = token;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

/*t_syntax	*ft_quote(t_input *input, t_syntax	*tree, t_token *token)
{
	if (input->current_token->type == T_SQUOTE)
	{
		eat(input, T_DQUOTE);
		tree = binap_nose(token, ft_others(input), NULL);
	}
	else if (input->current_token->type == T_DQUOTE)
	{
		eat(input, T_DQUOTE);
		tree = binap_nose(token, ft_others(input), NULL);
	}
	return (tree);
}

t_syntax	*ft_others(t_input *input)
{
	t_syntax	*tree;
	t_token		*token;

	token = input->current_token;
	tree = NULL;
	if (input->current_token->type == T_O_PARENT)
	{
		tree = ft_pipe(input);
		eat(input, T_C_PARENT);
	}
	else if (input->current_token->type == T_IDENTIFIER)
	{
		eat(input, T_IDENTIFIER);
		tree = binap_nose(token, ft_others(input), NULL); //ft_outfile_1(input)
	}
	tree = ft_quote(input, tree, token);
	return (tree);
}*/
