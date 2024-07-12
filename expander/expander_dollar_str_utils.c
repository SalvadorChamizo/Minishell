/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar_str_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:28:13 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/10 11:16:26 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	ft_skip_quote(char *str, char *new_text, int *i, int k)
{
	int	len;
	int	j;

	j = *i;
	len = ft_strlen(str);
	while (j < len && str[j] == '\'')
		new_text[k++] = str[j++];
	while (j < len && str[j] != '\'')
		new_text[k++] = str[j++];
	while (j < len && str[j] == '\'')
		new_text[k++] = str[j++];
	*i = j;
	return (k);
}

char	*remove_dollar_str(char	*str)
{
	char	*new_text;
	int		i;
	int		j;

	new_text = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			j = ft_skip_quote(str, new_text, &i, j);
		if (str[i] == '$')
		{
			while (str[i] != ' ' && str[i] != '\0')
				i++;
		}
		if (str[i])
			new_text[j++] = str[i];
		if (str[i] != '\0')
			i++;
	}
	new_text[j] = '\0';
	free(str);
	str = new_text;
	return (str);
}

void	ft_search_aux(char **env, t_dollar *dollar, char *new_text, int *flag)
{
	int		i;
	char	*env_var;
	char	*value;
	char	*new_value;

	i = 0;
	while (env[i])
	{
		env_var = get_variable_env(env[i]);
		if (ft_strcmp(dollar->variable, env_var) == 0)
		{
			value = get_value_env(env[i]);
			new_value = expand_quotes_str(value);
			dollar->j = 0;
			while (new_value[dollar->j])
				new_text[dollar->k++] = new_value[dollar->j++];
			free(new_value);
			*(dollar->flag) = 1;
			*flag = 1;
			free(env_var);
			break ;
		}
		free(env_var);
		i++;
	}
}

void	ft_search_env(char **env, t_dollar *dollar, char *new_text, char *str)
{
	int		j;
	int		flag;

	j = dollar->j;
	flag = 0;
	ft_search_aux(env, dollar, new_text, &flag);
	if (flag == 0)
	{
		if (str[j] == '$')
			new_text[dollar->k++] = str[j++];
		while (str[j] != '\0' && ft_isalnum(str[j]))
			new_text[dollar->k++] = str[j++];
	}
}

void	init_dollar(t_dollar **dollar, char **new_text, int *flag)
{
	*dollar = malloc(sizeof(t_dollar));
	if (!*dollar)
		return ;
	*new_text = malloc(sizeof(char) * 2048);
	if (!*new_text)
	{
		free(*dollar);
		*dollar = NULL;
		return ;
	}
	(*dollar)->flag = flag;
	(*dollar)->k = 0;
}
