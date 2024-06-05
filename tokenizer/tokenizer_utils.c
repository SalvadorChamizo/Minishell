/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:04:30 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/05 19:09:50 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

bool	isoperator(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '(' || c == ')')
		return (true);
	return (false);
}

void	ft_sop_def(t_input *mshll, t_token *nt, char *rt, t_tokentype t)
{
	nt->value = ft_substr(rt, mshll->pos, 1);
	if (!nt->value)
		return ;
	nt->type = t;
}

void	ft_dop_def(t_input *mshll, t_token *nt, char *rt, t_tokentype t)
{
	nt->value = ft_substr(rt, mshll->pos, 2);
	if (!nt->value)
		return ;
	nt->type = t;
	mshll->pos++;
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

void	ft_skip_spaces(t_input *input, char *text, t_token *new_token)
{
	new_token->space = false;
	if (ft_isspace(text[input->pos]))
	{
		while (ft_isspace(text[input->pos]))
			input->pos++;
		new_token->space = true;
	}
}
