/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:03:54 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/22 06:13:47 by schamizo         ###   ########.fr       */
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
	int				i;

	i = 0;
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
		}
		new_text[dollar->k++] = str[i++];
	}
	new_text[dollar->k] = '\0';
	flag = dollar->flag;
	free(dollar->variable);
	free(dollar);
	if (ft_strcmp(new_text, "") != 0)
	{
		free(str);
		str = new_text;
	}
	return (str);
}

char	*heredoc_dollar_list(char *str, t_assign *list, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	t_assign	*temp;
	int				i;

	i = 0;
	dollar = malloc(sizeof(t_dollar));
	new_text = malloc(sizeof(char) * 2048);
	dollar->flag = flag;
	if (!ft_check_dollar(str))
		return (str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollar->variable = get_variable(str, &i);
			temp = list;
			check_variable_copy2(temp, dollar, new_text);
		}
		new_text[dollar->k++] = str[i++];
	}
	free(dollar->variable);
	free(dollar);
	free(str);
	return (new_text);
}

char	*expand_status_heredoc(char *str, t_minishell *minishell)
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
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			dollar->variable = ft_strdup("?");
			i = i + 2;
			check_variable_copy(dollar, new_text, minishell);
		}
		if (str[i] && i < len)
		{
			new_text[dollar->j++] = str[i++];
		}
	}
	new_text[dollar->j] = '\0';
	free(dollar->variable);
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
		if (!minishell->list)
			str = remove_dollar_heredoc(str);
		else if (minishell->list)
		{
			str = heredoc_dollar_env(str, minishell->env, &flag);
			str = heredoc_dollar_list(str, minishell->list, &flag);
			if (flag == 0)
				str = remove_dollar_heredoc(str);
		}
	}
	return (str);
}
