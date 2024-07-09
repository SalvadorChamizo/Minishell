/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:03:54 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/09 18:04:41 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	*remove_dollar_heredoc(char	*str)
{
	char	*new_text;
	int		i;
	int		j;

	new_text = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			while (str[i] != ' ' && str[i] != '\0')
				i++;
		}
		new_text[j] = str[i];
		if (str[i] != '\0')
			i++;
		j++;
	}
	new_text[j] = '\0';
	free(str);
	return (new_text);
}

char	*heredoc_dollar_env(char *str, char **env, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	int			i;

	i = 0;
	init_dollar(&dollar, &new_text, flag);
	if (!new_text)
		return (str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollar->j = i;
			dollar->variable = get_variable(str, &i);
			env_variable(env, dollar, new_text, str);
			free(dollar->variable);
		}
		new_text[dollar->k++] = str[i++];
	}
	new_text[dollar->k] = '\0';
	flag = dollar->flag;
	free(dollar);
	str = status_heredoc_free(new_text, str);
	return (str);
}

char	*heredoc_dollar_list(char *str, t_assign *list, int *flag)
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
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollar->variable = get_variable(str, &i);
			copy_variable(list, dollar, new_text, str);
			free(dollar->variable);
		}
		if (str[i])
			new_text[dollar->k++] = str[i++];
	}
	flag = dollar->flag;
	free(dollar);
	str = status_heredoc_free(new_text, str);
	return (str);
}

char	*ft_expand_heredoc(char *str, t_minishell *minishell)
{
	int	flag;

	flag = 0;
	if (!str)
		return (str);
	if (ft_strnstr(str, "$?", ft_strlen(str)))
		str = expand_status_heredoc(str, minishell);
	if (ft_check_dollar(str))
	{
		if (minishell->list)
		{
			str = heredoc_dollar_env(str, minishell->env, &flag);
			str = heredoc_dollar_list(str, minishell->list, &flag);
			str = remove_dollar_heredoc(str);
		}
	}
	return (str);
}
