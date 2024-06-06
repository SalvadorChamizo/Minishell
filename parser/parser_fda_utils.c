/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fda_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:19:19 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/06 12:24:26 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	is_redirection_2(t_token *token)
{
	if (token->type == T_GREAT || token->type == T_LESS
		|| token->type == T_DLESS || token->type == T_DGREAT)
		return (1);
	else
		return (0);
}

int	ft_redirection(t_token *token, int state)
{
	if (is_redirection_2(token) && (state == 1 || state == 4 || state == 6))
		state = 3;
	else if (is_redirection_2(token) && state == 5)
		state = 7;
	return (state);
}

int	ft_word(t_token *token, int state)
{
	if ((token->type == T_IDENTIFIER || token->type == T_ASSING)
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
	else if (token->type == T_C_PARENT
		&& (state == 1 || state == 6 || state == 4))
		state = 5;
	return (state);
}
