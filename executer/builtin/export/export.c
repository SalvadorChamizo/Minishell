/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:12:02 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/15 18:03:49 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

int	mat_extenser(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
		i++;
	return (i);
}

void	ft_newenv(char ***env, char *str)
{
	int			i;
	char		**newenv;

	i = mat_extenser(env) + 2;
	newenv = malloc(sizeof(char *) * i);
	i = 0;
	while ((*env)[i])
	{
		newenv[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	new_env_manager(str, &newenv[i]);
	newenv[i + 1] = NULL;
	free(*env);
	*env = newenv;
}

int	env_exist(char **env, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] != '\0' && str[j] != '=' && str[j] != '+')
		j++;
	if (str[j] == '\0')
		return (0);
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, j))
		{
			if (str[j] == '+')
				ft_export_addiction(str, &env[i]);
			else
			{
				free(env[i]);
				env[i] = ft_strdup(str);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void	list_check(char *var, t_assign *list, char ***env)
{
	t_assign	*temp;
	char		*strtemp;
	char		*str;

	temp = list;
	while (temp)
	{
		if (!ft_strncmp(temp->variable, var, var_len(var)))
		{
			strtemp = ft_strjoin(temp->variable, "=");
			str = ft_strjoin(strtemp, temp->value);
			if (!env_exist(*env, str))
				ft_newenv(env, str);
			free(strtemp);
			free(str);
		}
		temp = temp->next;
	}
}

void	ft_export(t_ast *ast, t_minishell *minishell)
{
	t_ast		*tmp;
	char		*str;

	tmp = ast->left;
	minishell->status = 0;
	str = NULL;
	if (!tmp)
		export_print(minishell->env);
	while (tmp)
	{
		str = export_str_builder(&tmp);
		if (!identifier_check(str))
			minishell->status = 1;
		else if (ft_strchr(str, '='))
		{
			if (!env_exist(minishell->env, str))
				ft_newenv(&minishell->env, str);
		}
		else
			list_check(str, minishell->list, &minishell->env);
		tmp = tmp->left;
	}
}
