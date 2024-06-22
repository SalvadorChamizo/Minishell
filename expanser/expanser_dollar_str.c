/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_dollar_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 06:02:01 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/22 09:04:23 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	*remove_dollar_str(char	*str)
{
	char	*new_text;
	int		len;
	int		i;
	int		j;

	new_text = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			while (i < len && str[i] == '\'')
				new_text[j++] = str[i++];
			while (i < len && str[i] != '\'')
				new_text[j++] = str[i++];
			while (i < len && str[i] == '\'')
				new_text[j++] = str[i++];
		}
		if (i < len && str[i] == '$')
		{
			while (i < len && str[i] != ' ' && str[i] != '\0')
				i++;
		}
		if (i < len)
			new_text[j] = str[i];
		if (str[i] != '\0')
			i++;
		j++;
	}
	new_text[j] = '\0';
	free(str);
	return (new_text);
}

char	*str_dollar_env(char *str, char **env, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(str);
	dollar = malloc(sizeof(t_dollar));
	new_text = malloc(sizeof(char) * 2048);
	dollar->flag = flag;
	dollar->k = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (i < len && str[i] == '\'')
				new_text[dollar->k++] = str[i++];
			while (i < len && str[i] != '\'')
				new_text[dollar->k++] = str[i++];
			while (i < len && str[i] == '\'')
				new_text[dollar->k++] = str[i++];
		}
		if (i < len && str[i] == '$')
		{
			dollar->variable = get_variable(str, &i);
			check_variable_env(env, dollar, new_text);
			free(dollar->variable);
		}
		if (i < len && str[i])
		{
			new_text[dollar->k++] = str[i++];
		}
	}
	new_text[dollar->k] = '\0';
	flag = dollar->flag;
	free(dollar);
	if (ft_strcmp(new_text, "") != 0)
	{
		free(str);
		str = new_text;
	}
	return (str);
}

char	*str_dollar_list(char *str, t_assign *list, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	t_assign	*temp;
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(str);
	dollar = malloc(sizeof(t_dollar));
	new_text = malloc(sizeof(char) * 2048);
	dollar->flag = flag;
	if (!ft_check_dollar(str))
		return (str);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (i < len && str[i] == '\'')
				new_text[dollar->k++] = str[i++];
			while (i < len && str[i] != '\'')
				new_text[dollar->k++] = str[i++];
			while (i < len &&str[i] == '\'')
				new_text[dollar->k++] = str[i++];
		}
		if (i < len && str[i] == '$')
		{
			dollar->variable = get_variable(str, &i);
			temp = list;
			check_variable_copy2(temp, dollar, new_text);
			free(dollar->variable);
		}
		if (i < len && str[i])
			new_text[dollar->k++] = str[i++];
	}
	flag = dollar->flag;
	free(dollar);
	if (ft_strcmp(new_text, "") != 0)
	{
		free(str);
		str = new_text;
	}
	return (str);
}

char	*expand_status_str(char *str, t_minishell *minishell)
{
	t_dollar	*dollar;
	int			i;
	int			len;
	char		*new_text;

	i = 0;
	len = ft_strlen(str);
	dollar = malloc(sizeof(t_dollar));
	dollar->j = 0;
	new_text = malloc(sizeof(char) * 2048);
	while (str[i] && i < len)
	{
		if (str[i] == '\'')
		{
			//printf("Entra 1\n");
			while (i < len && str[i] == '\'')
				new_text[dollar->k++] = str[i++];
			while (i < len && str[i] != '\'')
				new_text[dollar->k++] = str[i++];
			while (i < len && str[i] == '\'')
				new_text[dollar->k++] = str[i++];
			//printf("%s\n", new_text);
		}
		if (i < len && str[i] == '$' && str[i + 1] == '?')
		{
			//printf("Entra 2\n");
			dollar->variable = ft_strdup("?");
			i = i + 2;
			check_variable_copy(dollar, new_text, minishell);
			free(dollar->variable);
		}
		if (i < len && str[i])
		{
			//printf("Entra 3\n");
			new_text[dollar->j++] = str[i++];
		}
	}
	//printf("Sale\n");
	new_text[dollar->j] = '\0';
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
		if (!minishell->list)
			str = remove_dollar_str(str);
		else if (minishell->list)
		{
			str = str_dollar_env(str, minishell->env, &flag);
			str = str_dollar_list(str, minishell->list, &flag);
			if (flag == 0)
				str = remove_dollar_str(str);
		}
	}
	return (str);
}
