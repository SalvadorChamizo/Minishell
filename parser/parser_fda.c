/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:09:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/01 14:36:26 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/bash.h"

void	ft_parser(t_input *input)
{
	t_token	*token;
	int		state;
	int		level;

	token = get_next_token(input);
	state = 1;
	level = 0;
	while (token->type != T_EOF)
	{
		if (token->type == T_O_PARENT && (state == 1 || state == 6))
			level++;
		else if (token->type == T_C_PARENT && (state == 1 || state == 6))
			level--;
		state = ft_parents(token, state);
		state = ft_pipe(token, state);
		state = ft_word(token, state);
		state = ft_redirection(token, state);
		free(token);
		token = get_next_token(input);
	}
	if ((state == 5 || state == 1 || state == 4) && level == 0)
		printf("OK\n");
	else
		printf("KO\n");
}
