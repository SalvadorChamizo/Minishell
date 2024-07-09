/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar_str_status.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:26:24 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/09 17:56:54 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

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

void	loop_status(char *s, t_minishell *mnshll, t_dollar *dollar, char *text)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i < len && s[i])
	{
		if (s[i] == '\'')
			dollar->j = ft_skip_quote(s, text, &i, dollar->j);
		if (i < len && s[i] == '$' && s[i + 1] == '?')
		{
			dollar->variable = ft_strdup("?");
			i = i + 2;
			check_variable_copy(dollar, text, mnshll);
			free(dollar->variable);
		}
		if (i < len && s[i])
			text[dollar->j++] = s[i++];
	}
	text[dollar->j] = '\0';
}

char	*expand_status_str(char *str, t_minishell *minishell)
{
	t_dollar	*dollar;
	char		*new_text;

	new_text = init_status(&dollar);
	if (!new_text)
		return (str);
	loop_status(str, minishell, dollar, new_text);
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
