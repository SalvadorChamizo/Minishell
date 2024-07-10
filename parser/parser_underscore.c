/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_underscore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:29:30 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/10 18:56:37 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	word_count(char *word)
{
	int	i;
	int	j;
	int	flag;

	underscore_init(&i, &j, &flag);
	while (word[i] != '\0')
	{
		if (word[i] == '\'' && flag != 2)
			flag = simple_quote_control(flag);
		else if (word[i] == '\"' && flag != 1)
			flag = double_quote_control(flag);
		else
			j++;
		i++;
	}
	return (j);
}

char	*quote_delete(char *word, char *ret)
{
	int	i;
	int	j;
	int	flag;

	underscore_init(&i, &j, &flag);
	while (word[i] != '\0')
	{
		if (word[i] == '\'' && flag != 2)
			flag = simple_quote_control(flag);
		else if (word[i] == '\"' && flag != 1)
			flag = double_quote_control(flag);
		else
		{
			ret[j] = word[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*skip_quotes(char *word)
{
	char	*ret;
	char	*new_word;
	int		i;

	i = word_count(word);
	ret = malloc(sizeof(char) * i + 1);
	if (ret == NULL)
		return (word);
	ret = quote_delete(word, ret);
	new_word = ft_strdup(ret);
	free(ret);
	return (new_word);
}

char	*word_selector(t_minishell *minishell, int *ret, int size)
{
	char	*word;
	char	*old_word;
	int		temp;

	word = NULL;
	temp = *ret;
	while (minishell->input->line[*ret] != '\0'
		&& !ft_isspace(minishell->input->line[*ret]))
		(*ret)++;
	word = ft_substr(minishell->input->line, temp - size, *ret);
	if (!word)
		return (NULL);
	old_word = word;
	word = skip_quotes(word);
	free(old_word);
	return (word);
}

void	ft_underscore(t_minishell *minishell, t_token *token)
{
	int		ret;
	int		size;
	char	*word;

	ret = minishell->input->pos;
	word = NULL;
	size = ft_strlen(token->value);
	if (ret - size != 0 && !ft_isspace(minishell->input->line[ret - size - 1]))
		return ;
	if (token->value)
		word = word_selector(minishell, &ret, size);
	while (ft_isspace(minishell->input->line[ret]))
		ret++;
	if (word && minishell->input->line[ret] == '\0')
	{
		if (minishell->underscore)
			free(minishell->underscore);
		minishell->underscore = word;
	}
	else if (word)
		free(word);
}
