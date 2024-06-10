/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:10:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/10 17:07:06 by saroca-f         ###   ########.fr       */
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

void	ft_freepath(char **path)
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

/*void	gotouser(char **env)
{
	char	*user;

	user = ft_strdup(getenv("USER"));
	regret_basic();
	if (chdir("home") == -1)
		printf("bash: cd: HOME not set\n");
	if (chdir(user) == -1)
		printf("bash: cd: %s: No such file or directory\n", user);
	free(user);
	pwd_update(env);
}*/
