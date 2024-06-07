/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:10:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/07 15:26:25 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

char	*wish_ensambler(char const *s1, char const *s2)
{
	char	*s3;
	char	*p;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = malloc(len1 + len2 + 2);
	if (s3 == NULL)
		return (NULL);
	p = s3;
	while (len1--)
		*p++ = *s1++;
	*p++ = '/';
	while (len2--)
		*p++ = *s2++;
	*p = '\0';
	return (s3);
}

int	regret_basic(void)
{
	char	*now;

	now = getcwd(NULL, 0);
	while (ft_strcmp(now, "/") != 0)
	{
		if (chdir("..") == -1)
			return (1);
		free(now);
		now = getcwd(NULL, 0);
	}
	free(now);
	return (0);
}

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

void	gotouser(char **env)
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
}
