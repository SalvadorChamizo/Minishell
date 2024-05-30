/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:12:02 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/30 10:07:12 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	export_free(char ***env, int i, int str)
{
	if (!str)
		free(*env);
	else
		free((*env)[i]);
}

int	mat_extenser(char **env)
{
	int i;

	i = 0;
	while(env[i])
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
	while((*env)[i])
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

void	ft_export(t_ast *ast, char ***env)
{
	t_ast		*tmp;
	int			i;

	tmp = ast->left;
	i = 0;
	if (!tmp)
	{
		while ((*env)[i] != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd((*env)[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
		return ;
	}
	while (tmp)
	{
		ft_newenv(env, tmp->token->value);
		tmp = tmp->left;
	}
}
