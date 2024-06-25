/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:09:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/25 11:40:40 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	check_identifier(t_token *token)
{
	if (token->type != T_IDENTIFIER && token->type != T_ASSING)
		return (0);
	return (1);
}

int	check_syntax(t_token *token, int state)
{
	if (token->type != T_C_PARENT)
	{
		if ((state == 1) && token->type != T_O_PARENT
			&& !is_redirection_2(token) && !check_identifier(token))
			return (0);
		if (state == 2 && token->type != T_O_PARENT
			&& !is_redirection_2(token) && !check_identifier(token))
			return (0);
		if (state == 6 && token->type != T_O_PARENT
			&& !is_redirection_2(token) && !check_identifier(token))
			return (0);
		if ((state == 4 || state == 5) && token->type != T_PIPE
			&& !is_redirection_2(token) && !check_identifier(token))
			return (0);
		if ((state == 3 || state == 7) && !check_identifier(token))
			return (0);
	}
	else
	{
		return (state);
	}
	return (state);
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

int	finish_fda(t_token **token, int state, int level)
{
	if ((state == 5 || state == 1 || state == 4) && level == 0)
	{
		free((*token)->value);
		free(*token);
		return (1);
	}
	else
	{
		syntax_problem(*token, level, state);
		return (0);
	}
}

int	ft_parser_fda(t_minishell *minishell)
{
	t_token	*token;
	int		state;
	int		level;

	token = get_next_token(minishell->input);
	state = 1;
	level = 0;
	while (token->type != T_EOF)
	{
		if (token->type == T_O_PARENT && (state == 1 || state == 6))
			level++;
		else if (token->type == T_C_PARENT
			&& (state == 1 || state == 6 || state == 4))
			level--;
		is_lva(minishell->input, token, minishell->env);
		state = parser_fda_aux(&token, state);
		if (state == 0)
			break ;
		token = get_next_token(minishell->input);
	}
	if (finish_fda(&token, state, level) == 1)
		return (1);
	else
		return (0);
}
