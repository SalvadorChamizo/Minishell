/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:46:42 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/09 18:47:29 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	s_quote_case(t_input *mshll, t_token *nt, char *rt, t_tokentype t)
{
	int	start;

	start = mshll->pos;
	mshll->pos++;
	while (mshll->line[mshll->pos] != '\'' && mshll->line[mshll->pos])
		mshll->pos++;
	if (mshll->line[mshll->pos] == '\'')
	{
		nt->value = ft_substr(rt, start, mshll->pos - start + 1);
		nt->type = t;
		return ;
	}
	else
	{
		printf("single quote do not close\n");
		exit (0);
	}
}

void	d_quote_case(t_input *mshll, t_token *nt, char *rt, t_tokentype t)
{
	int	start;

	start = mshll->pos;
	mshll->pos++;
	while (mshll->line[mshll->pos] != '\"' && mshll->line[mshll->pos])
		mshll->pos++;
	if (mshll->line[mshll->pos] == '\"')
	{
		nt->value = ft_substr(rt, start, mshll->pos - start + 1);
		nt->type = t;
		return ;
	}
	else
	{
		printf("double quote do not close\n");
		exit (0);
	}
}
