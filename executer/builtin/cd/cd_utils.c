/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:10:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/16 20:34:40 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

int	ft_chdir(char *order, char **env)
{
	if (chdir(order) == -1)
		return (-1);
	pwd_update(env);
	return (0);
}

void	point_maker(char **point, char *step)
{
	char	*ret;
	char	*tmp;

	ret = ft_strjoin(*point, "/");
	tmp = ft_strjoin(ret, step);
	free(*point);
	*point = tmp;
	free(ret);
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
