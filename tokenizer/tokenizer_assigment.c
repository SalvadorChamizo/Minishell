/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_assigment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 08:11:29 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/22 10:19:38 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

bool	is_assing(t_input *minishell, char *ret)
{
	int	i;
	int	flag;

	i = minishell->pos;
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
		minishell->pos = i;
		return (true);
	}
	else
		return (false);
}
