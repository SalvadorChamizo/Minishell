/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:35:13 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/26 17:25:38 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	*dollar_list_aux(t_ast *ast, t_dollar *dollar, char *new_text)
{
	int	*flag;

	flag = dollar->flag;
	free(dollar);
	if (ft_strcmp(new_text, "") != 0)
	{
		free(ast->token->value);
		ast->token->value = new_text;
	}
	else
		free(new_text);
	return (flag);
}



void	ft_dollar_list(t_ast *ast, t_assign *list, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	t_assign	*temp;
	int			i;

	i = 0;
	dollar = malloc(sizeof(t_dollar));
	if (!dollar)
		return ;
	new_text = malloc(sizeof(char) * 2048);
	if (!new_text)
		return ;
	dollar->flag = flag;
	if (!ft_check_dollar(ast->token->value))
	{
		free(new_text);
		free(dollar);
		return ;
	}
	while (ast->token->value[i])
	{
		if (ast->token->value[i] == '$')
		{
			dollar->j = i;
			dollar->variable = get_variable(ast->token->value, &i);
			temp = list;
			check_variable_copy2(temp, dollar, new_text, ast->token->value);
			free(dollar->variable);
		}
		if (ast->token->value[i])
			new_text[dollar->k++] = ast->token->value[i++];
	}
	new_text[dollar->k] = '\0';
		flag = dollar->flag;
	free(dollar);
	if (ft_strcmp(new_text, "") != 0)
	{
		free(ast->token->value);
		ast->token->value = new_text;
	}
	else
		free(new_text);
}
