/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:32:04 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/11 12:35:58 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

char	*export_str_builder(t_ast **tmp)
{
	char	*str;
	char	*tep;

	str = ft_strdup((*tmp)->token->value);
	tep = NULL;
	while ((*tmp)->left && (*tmp)->left->token->space == false)
	{
		(*tmp) = (*tmp)->left;
		tep = ft_strjoin(str, (*tmp)->token->value);
		free(str);
		str = tep;
	}
	return (str);
}

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
	(*newenv)[j] = '\0';
}

void	new_env_manager(char *str, char **newenv)
{
	int		j;
	int		flag;

	j = 0;
	flag = 0;
	while (str[j] != '=')
		j++;
	if (str[j - 1] == '+')
	{
		*newenv = malloc(sizeof(char) * (strlen(str)));
		flag = 1;
	}
	else
		*newenv = malloc(sizeof(char) * (strlen(str) + 1));
	new_env_write(str, newenv, flag);
}

void	ft_export_addiction(char *str, char **env)
{
	char	*new;
	char	*tmp;
	int		i;

	i = 0;
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
