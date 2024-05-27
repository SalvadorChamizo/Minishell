/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:17:58 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/27 20:00:44 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

t_token	*get_next_token(t_input *input);
t_ast	*ft_expr(t_input *input);
t_ast	*ft_outfile(t_input *input, t_idenlst **list);
t_ast	*ft_factor(t_input *input, t_idenlst **list);

t_ast	*ft_assignment(t_input *input, t_idenlst **list)
{
	t_token	*token;
	t_ast	*ast_node;

	ast_node = NULL;
	token = input->current_token;
	if (token->type == T_ASSING)
	{
		ft_eat(input, T_ASSING);
		ast_node = bi_node(NULL, token, ft_factor(input, list));
	}
	else if (token->type == T_O_PARENT)
	{
		ast_node = ft_expr(input);
		ft_eat(input, T_C_PARENT);
		return (ast_node);
	}
	return (ast_node);
}

t_ast	*ft_factor(t_input *input, t_idenlst **list)
{
	t_token		*token;
	t_ast		*ast_node;
	t_idenlst	*new_node;

	ast_node = ft_assignment(input, list);
	token = input->current_token;
	if (token->type == T_IDENTIFIER)
	{
		new_node = ft_lstnew_identifier(input->current_token);
		ft_lstadd_identifier(list, new_node);
		ft_eat(input, T_IDENTIFIER);
		ast_node = ft_outfile(input, list);
	}
	return (ast_node);
}

t_ast	*ft_term(t_input *input, t_idenlst **list)
{
	t_ast	*ast;
	t_token	*token;
	t_token	*token2;

	ast = ft_factor(input, list);
	token = input->current_token;
	if (input->current_token->type == T_LESS
		|| input->current_token->type == T_DLESS)
	{
		ft_eat_aux(input);
		token2 = input->current_token;
		ft_eat(input, T_IDENTIFIER);
		if (ast)
			ast = bi_node(new_i_node(token2), token, ast);
		else
			ast = bi_node(new_i_node(token2), token, ft_outfile(input, list));
	}
	return (ast);
}

t_ast	*ft_outfile(t_input *input, t_idenlst **list)
{
	t_ast	*ast;
	t_token	*token;
	t_token	*token2;

	ast = ft_term(input, list);
	token = input->current_token;
	if (input->current_token->type == T_GREAT
		|| input->current_token->type == T_DGREAT)
	{
		ft_eat_aux(input);
		token2 = input->current_token;
		ft_eat(input, T_IDENTIFIER);
		if (ast)
			ast = bi_node(new_i_node(token2), token, ast);
		else
			ast = bi_node(new_i_node(token2), token, ft_outfile(input, list));
	}
	return (ast);
}

t_ast	*ft_expr(t_input *input)
{
	t_ast		*ast;
	t_ast		*ast2;
	t_token		*token;
	t_idenlst	*list;

	list = NULL;
	ast2 = NULL;
	input->current_token = get_next_token(input);
	ast = ft_outfile(input, &list);
	token = input->current_token;
	if (input->current_token->type == T_PIPE)
		ast = bi_node(ast, token, ft_expr(input));
	printf("Hasta aquí bien\n");
	ast = ft_expr_aux(ast, ast2, &list);
	printf("Aquí nada\n");
	print_ast(ast);
	return (ast);
}
