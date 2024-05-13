/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:24:51 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/13 15:42:36 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_syntax	*ft_qu(t_input *input, t_syntax *tree, t_token *token)
{
	if (input->current_token->type == T_SQUOTE)
	{
		eat(input, T_DQUOTE);
		tree = binap_nose(token, NULL, NULL);
	}
	else if (input->current_token->type == T_DQUOTE)
	{
		eat(input, T_DQUOTE);
		tree = binap_nose(token, NULL, NULL);
	}
	return (tree);
}

t_syntax	*ft_inte(t_input *input)
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
		tree = binap_nose(token, NULL, NULL);
	}
	tree = ft_qu(input, tree, token);
	return (tree);
}

t_syntax	*ft_parent(t_input *input)
{
	t_syntax	*tree;
	t_token		*token;

	token = input->current_token;
	tree = NULL;
	if (input->current_token->type == T_O_PARENT)
	{
		token = input->current_token;
		tree = ft_pipe(input);
		eat(input, T_C_PARENT);
	}
	return (tree);
}

t_syntax	*ft_less(t_input *input)
{
	t_syntax	*tree;
	t_token		*token;

	tree = ft_parent(input);
	if (input->current_token->type == T_LESS)
	{
		token = input->current_token;
		eat(input, T_LESS);
		tree = binap_nose(token, ft_inte(input), ft_dgreat(input));
	}
	return (tree);
}

t_syntax	*ft_dless(t_input *input)
{
	t_syntax	*tree;
	t_token		*token;

	tree = ft_less(input);
	if (input->current_token->type == T_DLESS)
	{
		token = input->current_token;
		eat(input, T_DLESS);
		tree = binap_nose(token, ft_inte(input), ft_dgreat(input));
	}
	return (tree);
}

t_syntax	*ft_great(t_input *input)
{
	t_syntax	*tree;
	t_token		*token;

	tree = ft_dless(input);
	if (input->current_token->type == T_GREAT)
	{
		token = input->current_token;
		eat(input, T_GREAT);
		tree = binap_nose(token, ft_inte(input), ft_dgreat(input));
	}
	return (tree);
}

t_syntax	*ft_dgreat(t_input *input)
{
	t_syntax	*tree;
	t_token		*token;

	tree = ft_great(input);
	if (input->current_token->type == T_DGREAT)
	{
		token = input->current_token;
		eat(input, T_DGREAT);
		tree = binap_nose(token, ft_inte(input), ft_dgreat(input));
	}
	return (tree);
}

t_syntax	*redirection_case(t_syntax *tree_r, t_input *input)
{
	t_syntax	*ret;

	ret = tree_r;
	while (tree_r && tree_r->right)
		tree_r = tree_r->right;
	if (!tree_r)
		return (ft_dgreat(input));
	else
		tree_r->right = ft_dgreat(input);
	return (ret);
}

t_syntax	*ident_case(t_syntax *tree_i, t_input *input)
{
	t_syntax	*ret;

	ret = tree_i;
	while (tree_i && tree_i->left != NULL)
		tree_i = tree_i->left;
	if (!tree_i)
		return (ft_others_c(input));
	else
		tree_i->left = ft_others_c(input);
	return (ret);
}

t_syntax	*ft_others(t_input *input)
{
	t_syntax	*tree_i;
	t_syntax	*tree_r;

	tree_i = NULL;
	tree_r = NULL;
	while (input->current_token->type != T_PIPE
		&& input->current_token->type != T_EOF)
	{
		if (is_redir(input->current_token->type))
			tree_r = redirection_case(tree_r, input);
		else
			tree_i = ident_case(tree_i, input);
	}
	if (!tree_i)
		return (tree_r);
	tree_i->right = tree_r;
	return (tree_i);
}

t_syntax	*ft_pipe(t_input *input)
{
	t_syntax	*tree;
	t_token		*token;

	input->current_token = get_next_token(input);
	tree = ft_others(input);
	token = input->current_token;
	if (input->current_token->type == T_PIPE)

		tree = binap_nose(token, tree, ft_pipe(input));
	return (tree);
}
