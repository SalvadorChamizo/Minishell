/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:13:48 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/10 13:07:15 by saroca-f         ###   ########.fr       */
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

void	copy_variable(t_assign *temp, t_dollar *dollar, char *text, char *str)
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
				text[dollar->k++] = temp->value[dollar->j++];
			flag = 1;
			*(dollar->flag) = 1;
			break ;
		}
		temp = temp->next;
	}
	if (flag == 0)
	{
		if (str[j] == '$')
			text[dollar->k++] = str[j++];
		while (str[j] != '\0' && ft_isalnum(str[j]))
			text[dollar->k++] = str[j++];
	}
}

void	check_variable_copy(t_dollar *dollar, char *text, t_minishell *mnshll)
{
	char	*exit_status;

	dollar->k = 0;
	exit_status = NULL;
	if (ft_strcmp(dollar->variable, "?") == 0)
	{
		exit_status = ft_itoa(mnshll->status);
		while (exit_status[dollar->k])
			text[dollar->j++] = exit_status[dollar->k++];
	}
	free(exit_status);
}

char	*get_variable(char	*text, int *cur)
{
	char	*variable;
	int		start;

	variable = NULL;
	start = *cur + 1;
	if (text[*cur] == '$')
	{
		*cur = *cur + 1;
		while (text[*cur] != '\0' && (ft_isalnum(text[*cur])
				|| text[*cur] == '_'))
			*cur = *cur + 1;
		variable = ft_substr(text, start, *cur - start);
	}
	return (variable);
}
