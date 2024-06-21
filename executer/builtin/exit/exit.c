/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:44:55 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/21 21:12:20 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

void	exit_free(t_minishell **minishell, t_ast *ast, char *str)
{
	int	i;

	i = 0;
	if (str)
		free(str);
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

char	*str_maker(t_ast **ast)
{
	char	*str;
	char	*tep;

	str = NULL;
	tep = NULL;
	ft_putstr_fd("exit\n", 1);
	if (!(*ast))
		return (str);
	str = ft_strdup((*ast)->token->value);
	while ((*ast)->left	&& (*ast)->left->token->space == false)
	{
		(*ast) = (*ast)->left;
		tep = ft_strjoin(str, (*ast)->token->value);
		free(str);
		str = tep;
	}
	return (str);
}

int	ft_str_is_number(char *str)
{
	int		i;

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

void	ft_exit_text(t_minishell **minishell, t_ast *ast, char *str)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit_free(minishell, ast, str);
	exit (2);
}

void	ft_exit(t_minishell **minishell, t_ast *ast)
{
	int		i;
	char	*str;
	t_ast	*tmp;

	i = 0;
	tmp = NULL;
	if (ast->left)
		tmp = ast->left;
	str = str_maker(&tmp);
	if (str)
	{
		if (ft_str_is_number(str))
			i = atoi(str);
		else
			ft_exit_text(minishell, ast, str);
		if (tmp->left)
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			(*minishell)->status = 1;
			free(str);
			return ;
		}
	}
	exit_free(minishell, ast, str);
	exit(i);
}
