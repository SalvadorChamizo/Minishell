/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:52 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/30 12:33:12 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	is_redir(t_input *minishell, t_token *newtok, char *ret)
{
	char	c;
	char	d;

	c = ret[minishell->pos];
	d = 0;
	if (ret[minishell->pos + 1])
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

void	ft_operat(t_input *minishell, t_token *newtok, char *ret)
{
	char	c;

	c = ret[minishell->pos];
	if (c == '|')
		ft_sop_def(minishell, newtok, ret, T_PIPE);
	else if (c == '(')
		ft_sop_def(minishell, newtok, ret, T_O_PARENT);
	else if (c == ')')
		ft_sop_def(minishell, newtok, ret, T_C_PARENT);
	is_redir(minishell, newtok, ret);
	if (!newtok->value)
		return ;
	minishell->pos++;
}

bool	isidentifier(char c)
{
	if (ft_isspace(c) || isoperator(c))
		return (false);
	return (true);
}

void	identifer_case(t_input *minishell, t_token	*newtok, char *ret)
{
	int	start;

	start = minishell->pos;
	while (ret[minishell->pos] && isidentifier(ret[minishell->pos]))
		minishell->pos++;
	newtok->value = ft_substr(ret, start, minishell->pos - start);
	if (!newtok->value)
		return ;
	if (ft_strchr(newtok->value, '=') && newtok->value[0] != '=')
		newtok->type = T_ASSING;
	else
		newtok->type = T_IDENTIFIER;
}

t_token	*get_next_token(t_input *minishell)
{
	char		*ret;
	t_token		*newtok;

	ret = minishell->line;
	newtok = malloc(sizeof(t_token));
	if (!newtok)
		return (NULL);
	while (ret[minishell->pos])
	{
		ft_skip_spaces(minishell, ret);
		if (isidentifier(ret[minishell->pos]))
		{
			identifer_case(minishell, newtok, ret);
			return (newtok);
		}
		else if (isoperator(ret[minishell->pos]) && ret[minishell->pos])
		{
			ft_operat(minishell, newtok, ret);
			return (newtok);
		}
		minishell->pos++;
	}
	newtok->type = T_EOF;
	newtok->value = 0;
	return (newtok);
}
