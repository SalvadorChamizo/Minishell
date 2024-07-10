/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:09:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/10 12:47:07 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../bash.h"

int	check_identifier(t_token *token)
{
	if (token->type != T_IDENTIFIER && token->type != T_ASSING)
		return (0);
	return (1);
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
	state = ft_pipe_status(*token, state);
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
		ft_underscore(minishell, token);
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
