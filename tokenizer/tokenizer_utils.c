/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:04:30 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/25 11:42:04 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

bool	is_assing(t_input *input, char *ret)
{
	int	i;
	int	flag;

	i = input->pos;
	flag = 0;
	if (ret[i] == '=' || ft_isdigit(ret[i]))
		return (false);
	while (ret[i] && (!ft_isspace(ret[i]) || flag != 0))
	{
		if (ret[i] == '=')
			flag = 1;
		if (flag == 0 && !ft_isalnum(ret[i]) && ret[i] != '_'
			&& !(ret[i] == '+' && ret[i + 1] == '='))
			return (false);
		i++;
	}
	if (flag == 1)
	{
		input->pos = i;
		return (true);
	}
	else
		return (false);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

int	ft_skip_spaces(t_input *input, char *text, t_token *new_token)
{
	new_token->value = NULL;
	new_token->space = false;
	while (ft_isspace(text[input->pos]))
	{
		input->pos++;
		new_token->space = true;
	}
	if (text[input->pos] == '\0')
		return (1);
	return (0);
}
