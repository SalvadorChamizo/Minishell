/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:10:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/11 12:26:16 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

int	ft_chdir(char *order, char **env)
{
	int		i;

	i = 0;
	if (chdir(order) == -1)
		return (-1);
	pwd_update(env);
	return (0);
}

char	*point_maker(char *point, char *step)
{
	point = ft_strjoin(point, "/");
	point = ft_strjoin(point, step);
	return (point);
}

void	ft_cd_free_mat(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}
