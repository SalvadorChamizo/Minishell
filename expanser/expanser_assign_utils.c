/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_assign_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:01:01 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/22 11:21:40 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../bash.h"

void	quote_manage(char c, int *flag, int *i)
{
	if (c == '\'' && *flag != 2)
	{
		if (*flag == 0)
			*flag = 1;
		else
			*flag = 0;
		(*i)++;
	}
	if (c == '\"' && *flag != 1)
	{
		if (*flag == 0)
			*flag = 2;
		else
			*flag = 0;
		(*i)++;
	}
}

int	new_value_size(char *value)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (value[i])
	{
		quote_manage(value[i], &flag, &i);
		i++;
		j++;
	}
	return (j);
}

void	get_new_value(char *value, char **new_value)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (value[i])
	{
		quote_manage(value[i], &flag, &i);
		(*new_value)[j] = value[i];
		i++;
		j++;
	}
	(*new_value)[j] = '\0';
}

char	*lst_addiction(char *value, char *text, int i)
{
	char	*new_value;
	char 	*temp;
	
	temp = ft_substr(text, i + 1, ft_strlen(text) - i);
	new_value = ft_strjoin(value, temp);
	free(value);
	free(temp);
	return (new_value);
}

bool	list_act(char *text, int i, t_assign *temp, char *word)
{
	char		*new_value;

	while (temp)
	{
		if (!ft_strcmp(word, temp->variable))
		{
			if (text[i - 1] == '+')
			{
				new_value = lst_addiction(temp->value, text, i);
				free(word);
				temp->value = new_value;
				return (false);
			}
			else
			{
				new_value = ft_substr(text, i + 1, ft_strlen(text) - i);
				free(temp->value);
				free(word);
				temp->value = new_value;
				return (false);
			}
		}
		temp = temp->next;
	}
	return (true);
}
