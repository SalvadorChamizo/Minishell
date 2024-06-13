/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fda_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:02:29 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/12 16:09:42 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	print_error_syntax(int level, int state)
{
	if (level < 0)
	{
		ft_putstr_fd("bash: syntax error near ", 2);
		ft_putstr_fd("unexpected token `)'\n", 2);
	}
	if (level > 0 || state == 6)
	{
		ft_putstr_fd("bash: syntax error: ", 2);
		ft_putstr_fd("unexpected end of file\n", 2);
	}
	if (state == 3)
	{
		ft_putstr_fd("bash: syntax error near ", 2);
		ft_putstr_fd("unexpected token `newline'\n", 2);
	}
}

void	syntax_problem(t_token *token, int level, int state)
{
	print_error_syntax(level, state);
	if (!token->value)
	{
		free(token);
		return ;
	}
	else if (token->value)
	{
		ft_putstr_fd("bash: syntax error near ", 2);
		ft_putstr_fd("unexpected token `", 2);
		ft_putstr_fd(token->value, 2);
		ft_putstr_fd("'\n", 2);
		free(token->value);
		free(token);
	}
	else
	{
		free(token);
		ft_putstr_fd("bash: syntax error near ", 2);
		ft_putstr_fd("unexpected token `newline'\n", 2);
	}
}
