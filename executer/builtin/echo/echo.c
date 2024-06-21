/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:04:59 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/21 22:07:06 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

char	*str_echo_maker(t_ast **ast)
{
	char	*str;
	char	*tep;

	str = NULL;
	tep = NULL;
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

bool n_flag(t_ast **tmp)
{
	int		i;
	char	*str;
	t_ast	*ret;

	i = 0;
	ret = *tmp;
	str = str_echo_maker(&ret);
	if (str[i] != '-')
	{
		free(str);
		return (false);
	}
	i++;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0' && !ft_isspace(str[i]))
	{
		free(str);
		return (false);
	}
	*tmp = ret;
	free(str);
	return (true);
}

void	echo_print(t_ast *tmp)
{
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
	while (tmp && n_flag(&tmp))
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
