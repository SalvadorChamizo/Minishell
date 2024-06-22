/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_assign_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:01:01 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/22 10:29:42 by saroca-f         ###   ########.fr       */
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
