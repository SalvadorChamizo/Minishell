/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc_status.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:30:47 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/09 17:31:37 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	*status_heredoc_free(char *new_text, char *str)
{
	if (ft_strcmp(new_text, "") != 0)
	{
		free(str);
		str = new_text;
	}
	else
		free(new_text);
	return (str);
}

char	*expand_status_heredoc(char *str, t_minishell *minishell)
{
	t_dollar	*dollar;
	int			i;
	char		*new_text;

	i = 0;
	new_text = init_status(&dollar);
	if (!new_text)
		return (str);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			dollar->variable = ft_strdup("?");
			i = i + 2;
			check_variable_copy(dollar, new_text, minishell);
			free(dollar->variable);
		}
		if (str[i])
			new_text[dollar->j++] = str[i++];
	}
	new_text[dollar->j] = '\0';
	free(dollar);
	str = status_heredoc_free(new_text, str);
	return (str);
}
