/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct_ad.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:16:06 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/09 17:02:44 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redir(t_tokentype type)
{
	if (type == T_DGREAT)
		return (true);
	else if (type == T_GREAT)
		return (true);
	else if (type == T_DLESS)
		return (true);
	else if (type == T_LESS)
		return (true);
	return (false);
}

t_syntax	*ft_quote_c(t_input *input, t_syntax *tree, t_token *token)
{
	if (input->current_token->type == T_SQUOTE)
	{
		eat(input, T_DQUOTE);
		tree = binap_nose(token, ft_others_c(input), NULL);
	}
	else if (input->current_token->type == T_DQUOTE)
	{
		eat(input, T_DQUOTE);
		tree = binap_nose(token, ft_others_c(input), NULL);
	}
	return (tree);
}

t_syntax	*ft_others_c(t_input *input)
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
		tree = binap_nose(token, ft_others_c(input), NULL);
	}
	tree = ft_quote_c(input, tree, token);
	return (tree);
}
