/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:10:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/28 19:25:54 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

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

void	regret_basic(t_ast *tree, char **env)
{
	while (ft_strcmp(getcwd(NULL, 0), "/") != 0)
	{
		if (ft_chdir("..", env) == -1)
		{
			cd_error(tree->left->token->value);
			break ;
		}
	}
}

int	ft_chdir(char *order, char **env)
{
	char	*oldpath;
	int		i;

	i = 0;
	oldpath = getcwd(NULL, 0);
	if (chdir(order) == -1)
		return (-1);
	while (env[i] != NULL)
	{
		
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			env[i] = ft_strjoin("OLDPWD=", oldpath);
		i++;
	}
	return (0);
}
