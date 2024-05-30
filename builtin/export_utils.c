/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:32:04 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/30 11:43:09 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int var_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

void	ft_putenv_fd(char *s)
{
	int i;
	char *first;
	char *second;

	i = 0;
	first = ft_substr(s, 0, var_len(s));
	ft_putstr_fd(first, 1);
	write(1, "=\"", 2);
	second = ft_substr(s, var_len(s) + 1, ft_strlen(s));
	ft_putstr_fd(second, 1);
	write(1, "\"", 1);
	free(first);
	free(second);
}
