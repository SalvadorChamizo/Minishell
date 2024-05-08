/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:04:30 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/08 13:14:25 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	isoperator(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '(' || c == ')' || c == '\"'
		|| c == '\'')
		return (true);
	return (false);
}

void	ft_sop_def(t_input *mshll, t_token *nt, char *rt, t_tokentype t)
{
	nt->value = ft_substr(rt, mshll->pos, 1);
	nt->type = t;
}

void	ft_dop_def(t_input *mshll, t_token *nt, char *rt, t_tokentype t)
{
	nt->value = ft_substr(rt, mshll->pos, 2);
	nt->type = t;
	mshll->pos++;
}

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
