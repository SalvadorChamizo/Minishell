/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:44:55 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/06 15:06:39 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bash.h"

void	exit_free(t_minishell **minishell, t_ast *ast)
{
	rl_clear_history();
	free_ast(&ast);
	if ((*minishell)->list)
		ft_list_clear(&(*minishell)->list);
	free((*minishell)->input->line);
	free((*minishell)->input);
	free((*minishell));
}

void	ft_exit(t_minishell **minishell, t_ast *ast)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	if (ast->left)
	{
		if (isdigit(ft_atoi(ast->left->token->value)))
			i = ft_atoi(ast->left->token->value);
		else
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(ast->left->token->value, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_free(minishell, ast);
			exit (2);
		}
		if (ast->left->left)
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
		}
	}
	exit_free(minishell, ast);
    exit(i);
}
