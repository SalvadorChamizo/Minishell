/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:35:33 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/09 17:24:18 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	*get_variable_env(char	*text)
{
	char	*variable;
	int		i;

	variable = NULL;
	i = 0;
	while (text[i] != '=')
		i++;
	variable = ft_substr(text, 0, i);
	return (variable);
}

char	*get_value_env(char *text)
{
	char	*value;
	int		i;

	value = NULL;
	i = 0;
	while (text[i] != '=')
		i++;
	i++;
	value = ft_substr(text, i, ft_strlen(text) - i);
	return (value);
}

int	env_variable_loop(t_dollar *dollar, char *new_text, char **env)
{
	char	*env_var;
	char	*value;
	char	*new_value;
	int		i;

	i = 0;
	while (env[i])
	{
		env_var = get_variable_env(env[i]);
		if (ft_strcmp(dollar->variable, env_var) == 0)
		{
			value = get_value_env(env[i]);
			new_value = expand_quotes_str(value);
			while (new_value[dollar->j])
				new_text[dollar->k++] = new_value[dollar->j++];
			*(dollar->flag) = 1;
			free(env_var);
			return (1);
		}
		free(env_var);
		i++;
	}
	return (0);
}

void	env_variable(char **env, t_dollar *dollar, char *new_text, char *str)
{
	int		flag;
	int		j;

	j = dollar->j;
	dollar->j = 0;
	flag = env_variable_loop(dollar, new_text, env);
	if (flag == 0)
	{
		if (str[j] == '$')
			new_text[dollar->k++] = str[j++];
		while (str[j] != '\0' && ft_isalnum(str[j]))
			new_text[dollar->k++] = str[j++];
	}
}
