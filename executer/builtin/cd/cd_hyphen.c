/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_hyphen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:50:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/09 11:15:43 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

char	*get_hyphen(char **env)
{
	int		i;
	int		j;
	char	*hyphen;

	i = 0;
	j = 0;
	hyphen = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD", ft_strlen("OLDPWD")) == 0)
		{
			j = ft_strlen("OLDPWD");
			hyphen = ft_strdup(env[i] + j + 1);
			return (hyphen);
		}
		i++;
	}
	return (hyphen);
}

void	put_hyphen_error(char *hyphen, int flag)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(hyphen, 2);
	if (flag == 1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (flag == 2)
		ft_putstr_fd(": Permission denied\n", 2);
}

bool	cd_hyphen_norm(char *hyphen)
{
	if (access(hyphen, F_OK) < 0)
	{
		put_hyphen_error(hyphen, 1);
		return (false);
	}
	else if (access(hyphen, X_OK) < 0)
	{
		put_hyphen_error(hyphen, 2);
		return (false);
	}
	return (true);
}

bool	cd_hyphen(char **env)
{
	char	*hyphen;

	hyphen = get_hyphen(env);
	if (hyphen == NULL)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (false);
	}
	if (!cd_hyphen_norm(hyphen))
	{
		free(hyphen);
		return (false);
	}
    ft_putstr_fd(hyphen, 1);
    ft_putstr_fd("\n", 1);
	oldpwd_update(env);
	if (chdir(hyphen) < 0)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (false);
	}
	free(hyphen);
	pwd_update(env);
	return (true);
}
