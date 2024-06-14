/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:32:04 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/14 16:51:22 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

void	ft_export_addiction(char *str, char **env)
{
	char	*new;
	char 	*tmp;
	int		i;

	i = 0;
	printf("Entra\n");
	while (str[i] != '=')
		i++;
	new = ft_substr(str, i + 1, ft_strlen(str));
	tmp = (*env);
	(*env) = ft_strjoin(tmp, new);
	free(tmp);
}

int	var_len(char *str)
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
