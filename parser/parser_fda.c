/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:09:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/01 17:56:15 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

/*void	ft_parser_fda(t_input *input)
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
	{
		printf("bash: syntax error near unexpected token `%s'\n", token->value);
	}
}*/
//bash: syntax error near unexpected token `newline'

int	ft_parser_fda(t_input *input)
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
		if ((state == 1 || state == 5) && token->type != T_O_PARENT && !is_redirection_2(token) && token->type != T_IDENTIFIER && token->type != T_ASSING)
		{
			state = 0;
			break ;
		}
		if (state == 2 && token->type != T_O_PARENT && !is_redirection_2(token) && token->type != T_IDENTIFIER && token->type != T_ASSING)
		{
			state = 0;
			break ;
		}
		if (state == 6 && token->type != T_O_PARENT && !is_redirection_2(token) && token->type != T_IDENTIFIER && token->type != T_ASSING)
		{
			state = 0;
			break ;
		}
		if ((state == 4 || state == 5) && token->type != T_PIPE && !is_redirection_2(token) && token->type != T_IDENTIFIER && token->type != T_ASSING)
		{
			state = 0;
			break ;
		}
		if ((state == 3 || state == 7) && token->type != T_IDENTIFIER && token->type != T_ASSING)
		{
			state = 0;
			break ;
		}
		state = ft_parents(token, state);
		state = ft_pipe(token, state);
		state = ft_word(token, state);
		state = ft_redirection(token, state);
		free(token);
		token = get_next_token(input);
	}
	if ((state == 5 || state == 1 || state == 4) && level == 0)
		return (1);
	else
	{
		if (token->value)
			printf("bash: syntax error near unexpected token `%s'\n", token->value);
		else
			printf("bash: syntax error near unexpected token `newline'\n");
		return (0);
	}
}
