/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:12:02 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/07 15:27:29 by saroca-f         ###   ########.fr       */
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
	newenv[i] = malloc(sizeof(char) * ft_strlen(str) + 1);
	strcpy(newenv[i], str);
	newenv[i + 1] = NULL;
	free(*env);
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
	char			*strtemp;
	char			*str;

	temp = list;
	while (temp)
	{
		if (!ft_strncmp(temp->variable, var, var_len(var)))
		{
			strtemp = ft_strjoin(temp->variable, "=");
			str = ft_strjoin(temp->variable, strtemp);
			ft_newenv(env, str);
			free(strtemp);
			free(str);
		}
		temp = temp->next;
	}
}

void	ft_export(t_ast *ast, char ***env, t_minishell *minishell)
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
			if (!env_exist(*env, tmp->token->value))
				ft_newenv(env, tmp->token->value);
		else
			list_check(tmp->token->value, minishell->list, env);
		tmp = tmp->left;
	}
	minishell->status = 0;
}
