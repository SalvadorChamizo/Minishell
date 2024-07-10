/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 06:02:01 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/10 10:55:17 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

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
	init_dollar(&dollar, &new_text, flag);
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

void	process_list(char *str, t_assign *list, t_dollar *dollar, char *text)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '\'')
			dollar->k = ft_skip_quote(str, text, &i, dollar->k);
		if (i < len && str[i] == '$')
		{
			dollar->j = i;
			dollar->variable = get_variable(str, &i);
			copy_variable(list, dollar, text, str);
			free(dollar->variable);
		}
		if (i < len && str[i])
			text[dollar->k++] = str[i++];
	}
	text[dollar->k] = '\0';
}

char	*str_dollar_list(char *str, t_assign *list, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	int			i;

	i = 0;
	init_dollar(&dollar, &new_text, flag);
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
