/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:46:42 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/11 11:07:45 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	isquote(char c)
{
	if (c == '\'' || c == '\"' || ft_isspace(c) || isoperator(c))
		return (1);
	return (0);
}

void	s_quote_case(t_input *mshll, t_token *nt, char *rt)
{
	int	start;

	start = mshll->pos;
	mshll->pos++;
	while (mshll->line[mshll->pos] != '\'' && mshll->line[mshll->pos])
		mshll->pos++;
	if (mshll->line[mshll->pos] == '\'')
	{
		nt->value = ft_substr(rt, start, mshll->pos - start + 1);
		if (nt->value)
			mshll->pos++;
		return ;
	}
	else
	{
		printf("bash: syntax error: single quote do not close\n");
		nt->value = NULL;
		return ;
	}
}

void	d_quote_case(t_input *mshll, t_token *nt, char *rt)
{
	int	start;

	start = mshll->pos;
	mshll->pos++;
	while (mshll->line[mshll->pos] != '\"' && mshll->line[mshll->pos])
		mshll->pos++;
	if (mshll->line[mshll->pos] == '\"')
	{
		nt->value = ft_substr(rt, start, mshll->pos - start + 1);
		if (nt->value)
			mshll->pos++;
		return ;
	}
	else
	{
		printf("bash: syntax error: double quote do not close\n");
		nt->value = NULL;
		return ;
	}
}
