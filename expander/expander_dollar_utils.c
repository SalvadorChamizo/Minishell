/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:13:48 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/26 12:42:21 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	ft_check_dollar(char *text)
{
	int	i;

	i = 0;
	if (!text)
		return (0);
	while (text[i])
	{
		if (text[i] && text[i] == '$' && text[i + 1] != ' '
			&& text[i + 1] != '\0' && text[i + 1] != '\"')
			return (1);
		i++;
	}
	return (0);
}

void	check_variable_copy2(t_assign *temp, t_dollar *dollar, char *new_text, char *str)
{
	int	flag;
	int	j;

	flag = 0;
	j = dollar->j;
	dollar->j = 0;
	while (temp)
	{
		if (ft_strcmp(dollar->variable, temp->variable) == 0)
		{
			while (temp->value[dollar->j])
				new_text[dollar->k++] = temp->value[dollar->j++];
			flag = 1;
			*(dollar->flag) = 1;
			dollar->j = 0;
			break ;
		}
		temp = temp->next;
	}
	if (flag == 0)
	{
		if (str[j] == '$')
		{
			new_text[dollar->k++] = str[j++];
		}
		while (str[j] != '\0' && ft_isalnum(str[j]))
			new_text[dollar->k++] = str[j++];
	}
}

void	check_variable_copy(t_dollar *dollar, char *new_text, t_minishell *minishell)
{
	char	*exit_status;

	dollar->k = 0;
	exit_status = NULL;
	if (ft_strcmp(dollar->variable, "?") == 0)
	{
		exit_status = ft_itoa(minishell->status);
		while (exit_status[dollar->k])
			new_text[dollar->j++] = exit_status[dollar->k++];
	}
	free(exit_status);
}
