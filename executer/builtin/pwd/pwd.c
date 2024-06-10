/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:37:46 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/10 15:30:54 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

void	ft_pwd(t_minishell *minishell, char **env)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = getpwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		minishell->status = 0;
		return ;
	}
	while (env[i] && !pwd)
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			pwd = ft_substr(env[i], 4, ft_strlen(env[i]) - 4);
			pritf("%s\n", pwd);
			free(pwd);
			minishell->status = 0;
			return ;
		}
		i++;
	}
	minishell->status = 1;
}
