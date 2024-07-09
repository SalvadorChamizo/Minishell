/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 06:02:01 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/08 18:45:06 by schamizo         ###   ########.fr       */
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

void	init_str_env(t_dollar **dollar, char **new_text, int *flag)
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

void	process_env(char *str, char *new_text, t_dollar *dollar, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '\'')
			dollar->k = ft_skip_quote(str, new_text, &i, dollar->k);
		if (i < len && str[i] == '$')
		{
			dollar->j = i;
			dollar->variable = get_variable(str, &i);
			ft_search_env(env, dollar, new_text, str);
			free(dollar->variable);
		}
		if (i < len && str[i])
			new_text[dollar->k++] = str[i++];
	}
	new_text[dollar->k] = '\0';
}

char	*str_dollar_env(char *str, char **env, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(str);
	init_str_env(&dollar, &new_text, flag);
	if (!new_text)
		return (str);
	process_env(str, new_text, dollar, env);
	flag = dollar->flag;
	free(dollar);
	if (ft_strcmp(new_text, "") != 0 && *flag == 1)
	{
		free(str);
		str = new_text;
	}
	else
		free(new_text);
	return (str);
}

void	init_str_list(t_dollar **dollar, char **new_text, int *flag)
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

void	process_list(char *str, t_assign *list, t_dollar *dollar, char *new_text)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '\'')
			dollar->k = ft_skip_quote(str, new_text, &i, dollar->k);
		if (i < len && str[i] == '$')
		{
			dollar->j = i;
			dollar->variable = get_variable(str, &i);
			check_variable_copy2(list, dollar, new_text, str);
			free(dollar->variable);
		}
		if (i < len && str[i])
			new_text[dollar->k++] = str[i++];
	}
	new_text[dollar->k] = '\0';
}

char	*str_dollar_list(char *str, t_assign *list, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(str);
	init_str_list(&dollar, &new_text, flag);
	if (!new_text)
		return (str);
	if (!ft_check_dollar(str))
		return (str);
	process_list(str, list, dollar, new_text);
	flag = dollar->flag;
	free(dollar);
	if (ft_strcmp(new_text, "") != 0)
	{
		free(str);
		str = new_text;
	}
	else
		free(new_text);
	return (str);
}

char	*init_status(t_dollar **dollar)
{
	char	*new_text;

	*dollar = malloc(sizeof(t_dollar));
	if (!dollar)
		return (NULL);
	new_text = malloc(sizeof(char) * 2048);
	if (!new_text)
	{
		free(dollar);
		dollar = NULL;
		return (NULL);
	}
	(*dollar)->j = 0;
	return (new_text);
}

void	process_status(char *str, t_minishell *minishell, t_dollar *dollar, char *new_text)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len && str[i])
	{
		if (str[i] == '\'')
			dollar->j = ft_skip_quote(str, new_text, &i, dollar->j);
		if (i < len && str[i] == '$' && str[i + 1] == '?')
		{
			dollar->variable = ft_strdup("?");
			i = i + 2;
			check_variable_copy(dollar, new_text, minishell);
			free(dollar->variable);
		}
		if (i < len && str[i])
			new_text[dollar->j++] = str[i++];
	}
	new_text[dollar->j] = '\0';
}

char	*expand_status_str(char *str, t_minishell *minishell)
{
	t_dollar	*dollar;
	char		*new_text;

	new_text = init_status(&dollar);
	if (!new_text)
		return (str);
	process_status(str, minishell, dollar, new_text);
	free(dollar);
	if (ft_strcmp(new_text, "") != 0)
	{
		free(str);
		str = new_text;
	}
	else
		free(new_text);
	return (str);
}

char	*ft_expand_str(char *str, t_minishell *minishell)
{
	int	flag;

	flag = 0;
	if (!str)
		return (str);
	if (ft_strnstr(str, "$?", ft_strlen(str)))
		str = expand_status_str(str, minishell);
	if (ft_check_dollar(str))
	{
		if (minishell->list)
		{
			str = str_dollar_env(str, minishell->env, &flag);
			str = str_dollar_list(str, minishell->list, &flag);
			str = remove_dollar_str(str);
		}
	}
	return (str);
}
