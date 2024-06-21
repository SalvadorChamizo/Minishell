/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:04:59 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/21 19:27:00 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

bool n_flag(char *str)
{
	int i;

	i = 0;
	if (str[i] != '-')
		return (false);
	i++;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0' && !ft_isspace(str[i]))
		return (false);
	return (true);
}

void	echo_print(t_ast *tmp)
{
	//ft_putstr_fd(tmp->token->value, 1);
	if (ft_strcmp(tmp->token->value, "") != 0)
		printf("%s", tmp->token->value);
	else
		printf("");
	if (tmp->left && tmp->left->token->space)
		printf(" ");
}

void	ft_echo(t_ast *ast, t_minishell *minishell)
{
	t_ast	*tmp;
	int		flag;

	tmp = ast->left;
	if (!tmp)
	{
		printf("\n");
		return ;
	}
	flag = 0;
	while (tmp && n_flag(tmp->token->value))
	{
		flag = 1;
		tmp = tmp->left;
	}
	while (tmp)
	{
		echo_print(tmp);
		tmp = tmp->left;
	}
	if (!flag)
		printf("\n");
	minishell->status = 0;
}
