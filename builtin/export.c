/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:12:02 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/31 15:33:21 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	mat_extenser(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_newenv(char ***env, char *str)
{
	static int	i;
	int			flag;
	char		**newenv;

	flag = 0;
	if (i)
		flag = 1;
	i = mat_extenser(*env) + 2;
	newenv = malloc(sizeof(char *) * i);
	i = 0;
	while ((*env)[i])
	{
		newenv[i] = ft_strdup((*env)[i]);
		if (flag)
			export_free(env, i, 1);
		i++;
	}
	newenv[i] = malloc(sizeof(char) * ft_strlen(str) + 1);
	strcpy(newenv[i], str);
	newenv[i + 1] = NULL;
	if (flag)
		export_free(env, 0, 0);
	*env = newenv;
}

int	env_exist(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, var_len(str)))
		{
			free(env[i]);
			env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	list_check(char *var, t_assign_list *list, char ***env)
{
	t_assign_list	*temp;
	char			*str;

	temp = list;
	while (temp)
	{
		if (!ft_strncmp(temp->variable, var, var_len(var)))
		{
			str = ft_strjoin(temp->variable, ft_strjoin("=", temp->value));
			ft_newenv(env, str);
		}
		temp = temp->next;
	}
}

void	ft_export(t_ast *ast, char ***env, t_assign_list *list)
{
	t_ast		*tmp;
	int			i;

	tmp = ast->left;
	i = 0;
	if (!tmp)
	{
		while ((*env)[i] != NULL)
		{
			ft_putenv_fd((*env)[i]);
			i++;
		}
		return ;
	}
	while (tmp)
	{
		if (ft_strchr(tmp->token->value, '='))
		{
			if (!env_exist(*env, tmp->token->value))
				ft_newenv(env, tmp->token->value);
		}
		else
			list_check(tmp->token->value, list, env);
		tmp = tmp->left;
	}
}
