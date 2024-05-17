/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:13:08 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/17 13:24:49 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/bash.h"

void	ft_eat_aux(t_input *input)
{
	if (input->current_token->type == T_LESS
		|| input->current_token->type == T_DLESS)
	{
		if (input->current_token->type == T_LESS)
			ft_eat(input, T_LESS);
		else if (input->current_token->type == T_DLESS)
			ft_eat(input, T_DLESS);
	}
	else if (input->current_token->type == T_GREAT
		|| input->current_token->type == T_DGREAT)
	{
		if (input->current_token->type == T_GREAT)
			ft_eat(input, T_GREAT);
		else if (input->current_token->type == T_DGREAT)
			ft_eat(input, T_DGREAT);
	}
}
