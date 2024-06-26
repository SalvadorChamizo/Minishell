/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:35:33 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/26 11:53:10 by schamizo         ###   ########.fr       */
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

void	check_variable_env(char **env, t_dollar *dollar, char *new_text, char *str)
{
	int		i;
	char	*env_var;
	char	*value;
	char	*new_value;
	int		flag;
	int		j;

	j = dollar->j;
	dollar->j = 0;
	i = 0;
	flag = 0;
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
			flag = 1;
			dollar->j = 0;
			free(env_var);
			break ;
		}
		free(env_var);
		i++;
	}
	if (flag == 0)
	{
		if (str[j] == '$')
		{
			new_text[dollar->k++] = str[j++];
		}
		while (str[j] != '\0' && ft_isalnum(str[j]))
			new_text[dollar->k++] = str[j++];
	}
}

/*int	*dollar_env_aux(t_ast *ast, char *new_text, t_dollar *dollar)
{
	int	*flag;

	flag = dollar->flag;
	free(dollar);
	if (ft_strcmp(new_text, "") != 0)
	{
		free(ast->token->value);
		ast->token->value = new_text;
	}
	else
		free(new_text);
	return (flag);
}*/

/*void	ft_dollar_env(t_ast *ast, char **env, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	char		*str;
	int			i;

	i = 0;
	str = ast->token->value;
	dollar = malloc(sizeof(t_dollar));
	new_text = malloc(sizeof(char) * 2048);
	dollar->flag = flag;
	dollar->k = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollar->variable = get_variable(str, &i);
			check_variable_env(env, dollar, new_text);
			free(dollar->variable);
		}
		if (str[i])
			new_text[dollar->k++] = str[i++];
	}
	new_text[dollar->k] = '\0';
	flag = dollar_env_aux(ast, new_text, dollar);
}*/
