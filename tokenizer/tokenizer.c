/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:52 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/11 13:23:18 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_redirection(t_input *minishell, t_token *newtok, char *ret)
{
	char	c;
	char	d;

	c = ret[minishell->pos];
	d = ret[minishell->pos + 1];
	if (c == '<' && d != '<')
		ft_sop_def(minishell, newtok, ret, T_LESS);
	else if (c == '>' && d != '>')
		ft_sop_def(minishell, newtok, ret, T_GREAT);
	else if (c == '<' && d == '<')
		ft_dop_def(minishell, newtok, ret, T_DLESS);
	else if (c == '>' && d == '>')
		ft_dop_def(minishell, newtok, ret, T_DGREAT);
}

void	ft_operator(t_input *minishell, t_token *newtok, char *ret)
{
	char	c;

	c = ret[minishell->pos];
	if (c == '|')
		ft_sop_def(minishell, newtok, ret, T_PIPE);
	else if (c == '(')
		ft_sop_def(minishell, newtok, ret, T_O_PARENT);
	else if (c == ')')
		ft_sop_def(minishell, newtok, ret, T_C_PARENT);
	else if (c == '\'')
		s_quote_case(minishell, newtok, ret, T_SQUOTE);
	else if (c == '\"')
		d_quote_case(minishell, newtok, ret, T_DQUOTE);
	is_redirection(minishell, newtok, ret);
	minishell->pos++;
}

bool	isidentifier(char c)
{
	if (isspace(c) || isoperator(c))
		return (false);
	return (true);
}

void	identifer_case(t_input *minishell, t_token	*newtok, char *ret)
{
	int	start;

	start = minishell->pos;
	while (isidentifier(ret[minishell->pos]) && ret[minishell->pos])
		minishell->pos++;
	newtok->value = ft_substr(ret, start, minishell->pos - start);
	newtok->type = T_IDENTIFIER;
}

t_token	*get_next_token(t_input *minishell)
{
	char		*ret;
	t_token		*newtok;

	ret = minishell->line;
	newtok = malloc(sizeof(t_token));
	while (ret[minishell->pos])
	{
		while (isspace(ret[minishell->pos]) && ret[minishell->pos])
			minishell->pos++;
		if (isidentifier(ret[minishell->pos]))
		{
			identifer_case(minishell, newtok, ret);
			printf(BLUE"Token value:"RESET" %s\n", newtok->value);
			printf(BLUE"Token type:"RESET" %d\n\n", newtok->type);
			return (newtok);
		}
		else if (isoperator(ret[minishell->pos]) && ret[minishell->pos])
		{
			ft_operator(minishell, newtok, ret);
			printf(BLUE"Token value:"RESET" %s\n", newtok->value);
			printf(BLUE"Token type:"RESET" %d\n\n", newtok->type);
			return (newtok);
		}
		minishell->pos++;
	}
	newtok->type = T_EOF;
	newtok->value = 0;
	return (newtok);
}
