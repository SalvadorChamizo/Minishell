/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:04:59 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/07 15:26:45 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

void	echo_print(t_ast *tmp)
{
	if (ft_strcmp(tmp->token->value, ""))
		ft_putstr_fd(tmp->token->value, 1);
	else
		ft_putstr_fd("", 1);
	if (tmp->left && tmp->left->token->space)
		ft_putstr_fd(" ", 1);
}

void	ft_echo(t_ast *ast, t_minishell *minishell)
{
	t_ast	*tmp;
	int		flag;

	tmp = ast->left;
	if (!tmp)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	flag = 0;
	if (!ft_strcmp(tmp->token->value, "-n"))
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
		ft_putstr_fd("\n", 1);
	minishell->status = 0;
}