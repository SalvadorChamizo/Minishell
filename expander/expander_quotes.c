/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:32:23 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/09 17:33:27 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	*expand_quotes_str(char *str)
{
	char	*new_str;

	if (str == NULL)
		return (str);
	if (str[0] == '\"' || str[0] == '\'')
	{
		if (str[0] == '\"')
		{
			new_str = ft_strtrim(str, "\"");
			free(str);
			return (new_str);
		}
		else if (str[0] == '\'')
		{
			new_str = ft_strtrim(str, "\'");
			free(str);
			return (new_str);
		}
	}
	return (str);
}

void	expand_quotes(t_ast *ast)
{
	char	*str;

	if (ast == NULL)
		return ;
	if (ast->token->value[0] == '\"' || ast->token->value[0] == '\'')
	{
		if (ast->token->value[0] == '\"')
		{
			str = ft_strtrim(ast->token->value, "\"");
			free(ast->token->value);
			ast->token->value = str;
		}
		else if (ast->token->value[0] == '\'')
		{
			str = ft_strtrim(ast->token->value, "\'");
			free(ast->token->value);
			ast->token->value = str;
		}
	}
	expand_quotes(ast->left);
	expand_quotes(ast->right);
}
