/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_relative.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:57:10 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/11 12:29:51 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

void	cd_relative_free(char **step, char *point)
{
	ft_cd_free_mat(step);
	free(point);
}

void	print_cd_error(char *road, int flag, char **step, char *point)
{
	cd_relative_free(step, point);
	if (flag == 1)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd:", 2);
		ft_putstr_fd(" cannot access parent directories:", 2);
		ft_putstr_fd(" No such file or directory\n", 2);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(road, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

int	archive_checker(char *road, char *now)
{
	char	**step;
	char	*point;
	int		i;

	i = 0;
	step = ft_split(road, '/');
	point = now;
	while (step[i])
	{
		point = point_maker(point, step[i]);
		if (access(point, F_OK) < 0 && (!ft_strcmp(step[i], "..")
				|| !ft_strcmp(step[i], ".")))
		{
			print_cd_error(road, 1, step, point);
			return (0);
		}
		else if (access(point, F_OK) < 0)
		{
			print_cd_error(road, 2, step, point);
			return (0);
		}
		i++;
	}
	cd_relative_free(step, point);
	return (1);
}

int	cd_relative_checker(char *road, char **env)
{
	char	*now;
	int		i;

	i = 0;
	now = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			now = ft_strdup(env[i] + 4);
			break ;
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
