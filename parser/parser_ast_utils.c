/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:13:08 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/25 12:07:27 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	ft_eat(t_input *input, t_tokentype type)
{
	if (input->current_token->type == type)
		input->current_token = get_next_token(input);
}

void	ft_eat_aux(t_input *input)
{
	if (input->current_token->type == T_LESS
		|| input->current_token->type == T_DLESS)
	{
		if (input->current_token->type == T_LESS)
			ft_eat(input, T_LESS);
		else if (input->current_token->type == T_DLESS)
			ft_eat(input, T_DLESS);
	}
	else if (input->current_token->type == T_GREAT
		|| input->current_token->type == T_DGREAT)
	{
		if (input->current_token->type == T_GREAT)
			ft_eat(input, T_GREAT);
		else if (input->current_token->type == T_DGREAT)
			ft_eat(input, T_DGREAT);
	}
}

int	is_redirection(t_token *token)
{
	if (token->type == T_GREAT || token->type == T_DGREAT
		|| token->type == T_LESS || token->type == T_DLESS)
		return (1);
	return (0);
}

t_ast	*ft_pipe_aux(t_ast *ast, t_ast *ast2, t_idenlst **list)
{
	t_ast	*ast3;

	ast3 = NULL;
	if (*list)
		ast2 = iden_node(*list);
	if (!ast && ast2)
		return (ast2);
	if (ast2 && ast && ast->right == NULL && ast->token->type == T_PIPE)
	{
		ast->right = ast2;
		return (ast);
	}
	if (ast2 && ast && ast->token->type != T_PIPE)
	{
		ast2->right = ast;
		return (ast2);
	}
	if (ast2 && ast && ast->right != NULL && ast->token->type == T_PIPE)
	{
		ast3 = ast->left;
		ast2->right = ast3;
		ast->left = ast2;
		return (ast);
	}
	return (ast);
}
