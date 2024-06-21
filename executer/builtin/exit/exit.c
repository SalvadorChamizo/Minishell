/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:44:55 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/19 19:32:35 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

void	exit_free(t_minishell **minishell, t_ast *ast)
{
	int	i;

	i = 0;
	rl_clear_history();
	free_ast(&ast);
	if ((*minishell)->list)
		ft_list_clear(&(*minishell)->list);
	free((*minishell)->input->line);
	free((*minishell)->input);
	while ((*minishell)->env[i])
	{
		free((*minishell)->env[i]);
		i++;
	}
	free((*minishell)->env);
	free((*minishell));
}

int	ft_strisnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_minishell **minishell, t_ast *ast)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	if (ast->left)
	{
		if (ft_strisnumber(ast->left->token->value))
			i = ft_atoi(ast->left->token->value);
		if (!ft_strisnumber(ast->left->token->value))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(ast->left->token->value, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_free(minishell, ast);
			exit (2);
		}
		else if (ast->left->left)
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			(*minishell)->status = 1;
			return ;
		}
	}
	exit_free(minishell, ast);
	exit(i);
}
