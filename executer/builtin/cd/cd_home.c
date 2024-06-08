/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:10:25 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/08 10:54:14 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

char   *get_home(char **env)
{
	int		i;
	int		j;
	char	*home;

	i = 0;
	j = 0;
	home = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME", ft_strlen("HOME")) == 0)
		{
			j = ft_strlen("HOME");
			home = ft_strdup(env[i] + j + 1);
			return (home);
		}
		i++;
	}
	return (home);
}

void	put_home_error(char *home, int flag)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(home, 2);
	if (flag == 1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (flag == 2)
		ft_putstr_fd(": Permission denied\n", 2);
}

bool	cd_home_norm(char *home)
{
	if (access(home, F_OK) < 0)
	{
		put_home_error(home, 1);
		return (false);
	}
	else if (access(home, X_OK) < 0)
	{
		put_home_error(home, 2);
		return (false);
	}
	return (true);
}

bool	cd_home(char **env)
{
	char	*home;

	home = get_home(env);
	if (home == NULL)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (false);
	}
	if (!cd_home_norm(home))
	{
		free(home);
		return (false);
	}
	if (chdir(home) < 0)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (false);
	}
	free(home);
	return (true);
}
