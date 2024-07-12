/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:46:42 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/25 11:30:41 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"' || ft_isspace(c) || is_operator(c))
		return (1);
	return (0);
}

void	s_quote_case(t_input *input, t_token *nt, char *rt)
{
	int	start;

	start = input->pos;
	input->pos++;
	while (input->line[input->pos] != '\'' && input->line[input->pos])
		input->pos++;
	if (input->line[input->pos] == '\'')
	{
		nt->value = ft_substr(rt, start, input->pos - start + 1);
		if (nt->value)
			input->pos++;
		return ;
	}
	else
	{
		ft_putstr_fd("bash: syntax error: single quote do not close\n", 2);
		nt->value = NULL;
		return ;
	}
}

void	d_quote_case(t_input *input, t_token *nt, char *rt)
{
	int	start;

	start = input->pos;
	input->pos++;
	while (input->line[input->pos] != '\"' && input->line[input->pos])
		input->pos++;
	if (input->line[input->pos] == '\"')
	{
		nt->value = ft_substr(rt, start, input->pos - start + 1);
		if (nt->value)
			input->pos++;
		return ;
	}
	else
	{
		ft_putstr_fd("bash: syntax error: double quote do not close\n", 2);
		nt->value = NULL;
		return ;
	}
}
