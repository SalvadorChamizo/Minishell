/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:09:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/06 12:23:25 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	is_identifier(t_token *token)
{
	if (token->type != T_IDENTIFIER && token->type != T_ASSING)
		return (0);
	return (1);
}

int	check_syntax(t_token *token, int state)
{
	if ((state == 1 || state == 5) && token->type != T_O_PARENT
		&& !is_redirection_2(token) && !is_identifier(token))
		return (0);
	if (state == 2 && token->type != T_O_PARENT
		&& !is_redirection_2(token) && !is_identifier(token))
		return (0);
	if (state == 6 && token->type != T_O_PARENT
		&& !is_redirection_2(token) && !is_identifier(token))
		return (0);
	if ((state == 4 || state == 5) && token->type != T_PIPE
		&& !is_redirection_2(token) && !is_identifier(token))
		return (0);
	if ((state == 3 || state == 7) && !is_identifier(token))
		return (0);
	return (state);
}

void	syntax_problem(t_token *token)
{
	if (!token->value)
		return ;
	else if (token->value)
	{
		printf("bash: syntax error near unexpected token `%s'\n", token->value);
		free(token->value);
		free(token);
	}
	else
	{
		free(token);
		printf("bash: syntax error near unexpected token `newline'\n");
	}
}

int	parser_fda_aux(t_token **token, int state)
{
	if ((*token)->value == NULL)
	{
		state = 0;
		return (state);
	}
	state = check_syntax(*token, state);
	if (state == 0)
		return (state);
	state = ft_parents(*token, state);
	state = ft_pipe(*token, state);
	state = ft_word(*token, state);
	state = ft_redirection(*token, state);
	free((*token)->value);
	free(*token);
	return (state);
}

int	ft_parser_fda(t_input *input)
{
	t_token	*token;
	int		state;
	int		level;

	token = get_next_token(input);
	state = 1;
	level = 0;
	while (token->type != T_EOF)
	{
		if (token->type == T_O_PARENT && (state == 1 || state == 6))
			level++;
		else if (token->type == T_C_PARENT && (state == 1 || state == 6))
			level--;
		state = parser_fda_aux(&token, state);
		if (state == 0)
			break ;
		token = get_next_token(input);
	}
	if ((state == 5 || state == 1 || state == 4) && level == 0)
		return (1);
	else
	{
		syntax_problem(token);
		return (0);
	}
}
