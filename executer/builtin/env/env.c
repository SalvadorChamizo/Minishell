/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:30:48 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/09 14:57:58 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

bool	check_flag(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		i++;
		while (str[i] == 'i')
			i++;
	}
	if (str[i] == '\0' || ft_isspace(str[i]))
		return (true);
	return (false);
}

void	lst_case(t_assign *list)
{
	t_assign	*tmp;

	tmp = list;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}

void	true_env_case(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	ft_env(t_ast *ast, t_minishell *minishell)
{
	if (ast->left && check_flag(ast->left->token->value) == true)
		lst_case(minishell->list);
	else
		true_env_case(minishell->env);
	minishell->status = 0;
}
