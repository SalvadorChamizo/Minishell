/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:46:42 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/05 18:33:45 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	s_quote_case(t_input *mshll, t_token *nt, char *rt)
{
	int	start;

	start = mshll->pos;
	mshll->pos++;
	while (mshll->line[mshll->pos] != '\'' && mshll->line[mshll->pos])
		mshll->pos++;
	if (mshll->line[mshll->pos] == '\'')
	{
		nt->value = ft_substr(rt, start - 1, mshll->pos - start + 1);
		mshll->pos++;
		return ;
	}
	else
	{
		printf("Bash: syntax error: single quote do not close\n");
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
		mshll->pos++;
		return ;
	}
	else
	{
		printf("Bash: syntax error: double quote do not close\n");
		return ;
	}
}
