/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:53:32 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/11 11:50:47 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

void	oldpwd_update(char **env)
{
	char	*oldpwd;
	int		i;

	i = 0;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		return ;
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", oldpwd);
			free(oldpwd);
			return ;
		}
		i++;
	}
	free(oldpwd);
}

void	pwd_update(char **env)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("bash: cd: PWD not set\n", 2);
		return ;
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", pwd);
			free(pwd);
			return ;
		}
		i++;
	}
	free(pwd);
}
