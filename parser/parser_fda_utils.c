/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fda_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:19:19 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/01 14:35:25 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/bash.h"

int	is_redirection(t_token *token)
{
	if (token->type == T_GREAT || token->type == T_LESS
		|| token->type == T_DLESS || token->type == T_DGREAT)
		return (1);
	else
		return (0);
}

int	ft_redirection(t_token *token, int state)
{
	if (is_redirection(token) && (state == 1 || state == 4 || state == 6))
		state = 3;
	else if (is_redirection(token) && state == 5)
		state = 7;
	return (state);
}

int	ft_word(t_token *token, int state)
{
	if (token->type == T_IDENTIFIER
		&& (state == 1 || state == 3 || state == 4 || state == 6))
		state = 4;
	else if (token->type == T_IDENTIFIER && state == 7)
		state = 5;
	return (state);
}

int	ft_pipe(t_token *token, int state)
{
	if (token->type == T_PIPE && (state == 4 || state == 5))
		state = 6;
	return (state);
}

int	ft_parents(t_token *token, int state)
{
	if (token->type == T_O_PARENT && (state == 1 || state == 6))
		state = 1;
	else if (token->type == T_C_PARENT && (state == 1 || state == 6))
		state = 5;
	return (state);
}
