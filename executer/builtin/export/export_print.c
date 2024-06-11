/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:18:19 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/11 11:03:20 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

void	ft_putenv_fd(char *s)
{
	int		i;
	char	*first;
	char	*second;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	first = ft_substr(s, 0, var_len(s));
	ft_putstr_fd(first, 1);
	write(1, "=\"", 2);
	second = ft_substr(s, var_len(s) + 1, ft_strlen(s));
	ft_putstr_fd(second, 1);
	write(1, "\"", 1);
	ft_putstr_fd("\n", 1);
	free(first);
	free(second);
}

char	*next_env(char **env, char *str)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], str) > 0 && (!ret || ft_strcmp(env[i], ret) < 0))
			ret = env[i];
		i++;
	}
	return (ret);
}

void	export_print(char **env)
{
	int		i;
	char	*str;
	char	*ret;

	i = 0;
	str = env[i];
	while (env[i])
	{
		if (ft_strcmp(str, env[i]) > 0)
			str = env[i];
		i++;
	}
	ft_putenv_fd(str);
	while (1)
	{
		ret = next_env(env, str);
		if (!ret)
			return ;
		str = ret;
		ft_putenv_fd(str);
	}
}
