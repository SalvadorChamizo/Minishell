/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:52 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/25 11:28:56 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

bool	is_identifier(char c)
{
	if (c == '\0' || ft_isspace(c) || is_operator(c))
		return (false);
	return (true);
}

void	identifer_case(t_input *input, t_token	*newtok, char *ret)
{
	int	start;

	if (ret[input->pos] == '\0')
		return ;
	start = input->pos;
	if (is_assing(input, ret))
	{
		newtok->value = ft_substr(ret, start, input->pos - start);
		newtok->type = T_ASSING;
		return ;
	}
	else if (ret[input->pos] == '\'')
		s_quote_case(input, newtok, ret);
	else if (ret[input->pos] == '\"')
		d_quote_case(input, newtok, ret);
	else
	{
		while (ret[input->pos] && !is_quote(ret[input->pos]))
			input->pos++;
		newtok->value = ft_substr(ret, start, input->pos - start);
	}
	if (!newtok->value)
		return ;
	else
		newtok->type = T_IDENTIFIER;
}

t_token	*ft_each_case(t_input *input, t_token *newtok, char *ret)
{
	if (is_identifier(ret[input->pos]))
	{
		identifer_case(input, newtok, ret);
		return (newtok);
	}
	else if (is_operator(ret[input->pos]))
	{
		ft_operator(input, newtok, ret);
		return (newtok);
	}
	else
		return (newtok);
}

t_token	*get_next_token(t_input *input)
{
	char		*ret;
	t_token		*newtok;

	ret = input->line;
	newtok = malloc(sizeof(t_token));
	if (!newtok)
		return (NULL);
	while (ret[input->pos])
	{
		if (ft_skip_spaces(input, ret, newtok))
			break ;
		if (is_identifier(ret[input->pos])
			|| is_operator(ret[input->pos]))
		{
			ft_each_case(input, newtok, ret);
			return (newtok);
		}
		input->pos++;
	}
	newtok->type = T_EOF;
	newtok->value = 0;
	return (newtok);
}
