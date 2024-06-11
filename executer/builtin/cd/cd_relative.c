/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_relative.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:57:10 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/11 10:26:20 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

int	archive_checker(char *road, char *now)
{
	char	**step;
	char	*point;
	int		i;

	i = 0;
	step = ft_split(road, '/');
	point = now;
	while(step[i])
	{
		point = ft_strjoin(point, "/");
		point = ft_strjoin(point, step[i]);
		if (access(point, F_OK) < 0 && (!ft_strcmp(step[i], "..")
			|| !ft_strcmp(step[i], ".")))
		{
			ft_putstr_fd("cd: error retrieving current directory: getcwd:", 2);
			ft_putstr_fd(" cannot access parent directories:", 2);
			ft_putstr_fd(" No such file or directory\n", 2);
			return (0);
		}
		else if (access(point, F_OK) < 0)
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(road, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	cd_relative_checker(char *road, char **env)
{
	char *now;

	int i = 0;
	now = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			now = ft_strdup(env[i] + 4);
			break;
		}
		i++;
	}
	if (!archive_checker(road, now))
		return (0);
	else if (access(road, X_OK) < 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(road, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (0);
	}
	return (1);
}

bool	cd_relative(char *rout, char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(rout, '/');
	if (!cd_relative_checker(rout, env))
		return (false);
	oldpwd_update(env);
	while (path[i])
	{
		ft_chdir(path[i], env);
		free(path[i]);
		i++;
	}
	free(path);
	return (true);
}