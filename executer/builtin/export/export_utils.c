/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:32:04 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/15 13:18:54 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

void	new_env_write(char *str, char **newenv, int flag)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+' && flag == 1)
		{
			i++;
			flag = 0;
		}
		(*newenv)[j] = str[i];
		i++;
		j++;
	}
}

void	new_env_manager(char *str, char **newenv)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	while (str[j] != '=')
		j++;
	if (str[j - 1] == '+')
	{
		*newenv = malloc(sizeof(char) * j);
		flag = 1;
	}
	else
		*newenv = malloc(sizeof(char) * j + 1);
	j = 0;
	new_env_write(str, newenv, flag);
	(*newenv)[i] = '\0';
}

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
