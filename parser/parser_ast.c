/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:17:58 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/25 12:04:47 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

t_ast	*ft_assignment(t_input *input, t_idenlst **list)
{
	t_token	*token;
	t_ast	*ast_node;

	ast_node = NULL;
	token = input->current_token;
	if (token->type == T_ASSING && !*list)
	{
		ft_eat(input, T_ASSING);
		ast_node = bi_node(NULL, token, ft_identifier(input, list));
	}
	else if (token->type == T_O_PARENT)
	{
		ast_node = ft_pipe(input);
		ft_eat(input, T_C_PARENT);
		return (ast_node);
	}
	return (ast_node);
}

t_ast	*ft_identifier(t_input *input, t_idenlst **list)
{
	t_token		*token;
	t_ast		*ast_node;
	t_idenlst	*new_node;

	ast_node = ft_assignment(input, list);
	token = input->current_token;
	if ((token->type == T_IDENTIFIER || token->type == T_ASSING) && list)
	{
		new_node = ft_lstnew_identifier(input->current_token);
		ft_lstadd_identifier(list, new_node);
		if (token->type == T_IDENTIFIER)
			ft_eat(input, T_IDENTIFIER);
		if (token->type == T_ASSING)
			ft_eat(input, T_ASSING);
		ast_node = ft_outfile(input, list);
	}
	return (ast_node);
}

t_ast	*ft_infile(t_input *input, t_idenlst **list)
{
	t_ast	*ast;
	t_token	*token;
	t_token	*token2;

	ast = ft_identifier(input, list);
	token = input->current_token;
	if (input->current_token->type == T_LESS
		|| input->current_token->type == T_DLESS)
	{
		ft_eat_aux(input);
		token2 = input->current_token;
		if (token2->type == T_IDENTIFIER)
			ft_eat(input, T_IDENTIFIER);
		if (token2->type == T_ASSING)
			ft_eat(input, T_ASSING);
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

	ast = ft_infile(input, list);
	token = input->current_token;
	if (input->current_token->type == T_GREAT
		|| input->current_token->type == T_DGREAT)
	{
		ft_eat_aux(input);
		token2 = input->current_token;
		if (token2->type == T_IDENTIFIER)
			ft_eat(input, T_IDENTIFIER);
		if (token2->type == T_ASSING)
			ft_eat(input, T_ASSING);
		if (ast)
			ast = bi_node(new_i_node(token2), token, ast);
		else
			ast = bi_node(new_i_node(token2), token, ft_outfile(input, list));
	}
	return (ast);
}

t_ast	*ft_pipe(t_input *input)
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
	{
		ast = bi_node(ast, token, ft_pipe(input));
	}
	ast = ft_pipe_aux(ast, ast2, &list);
	if (token->type == T_EOF)
		free(token);
	return (ast);
}
