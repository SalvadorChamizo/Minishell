/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:53:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/04 18:40:36 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	ft_check_dollar(char *text)
{
	int	i;

	i = 0;
	if (!text)
		return (0);
	while (text[i])
	{
		if (text[i] == '$' && text[i + 1] != ' '
			&& text[i + 1] != '\0' && text[i + 1] != '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*remove_dollar(t_ast *ast)
{
	char	*text;
	char	*new_text;
	int		i;
	int		j;

	text = ft_strdup(ast->token->value);
	new_text = malloc(sizeof(char) * ft_strlen(text));
	i = 0;
	j = 0;
	while (text[i] != '\0')
	{
		if (text[i] == '$')
		{
			while (text[i] != ' ' && text[i] != '\0')
				i++;
		}
		new_text[j] = text[i];
		if (text[i] != '\0')
			i++;
		j++;
	}
	new_text[j] = '\0';
	return (new_text);
}

char	*get_variable(char	*text, int *cur)
{
	char	*variable;
	int		i;
	int		len;

	variable = NULL;
	len = 0;
	i = *cur + 1;
	if (text[*cur] == '$')
	{
		while (text[*cur] != ' ' && text[*cur] != '\0')
		{
			*cur = *cur + 1;
			len++;
		}
		variable = malloc(sizeof(char) * len);
		len = 0;
		while (text[i] != ' ' && text[i] != '\0' && text[i] != '\"')
		{
			variable[len] = text[i];
			len++;
			i++;
		}
	}
	variable[len] = '\0';
	return (variable);
}

/*char	*ft_copy_value(char *new_text, char	*value, int	*k, int	*flag)
{
	int	j;

	j = 0;
	while (value[j])
	{
		new_text[*k] = value[j];
		j++;
		*k++;
	}
	*flag = 1;
	j = 0;
}*/

void	ft_dollar_list(t_ast *ast, t_assign_list *list, int *flag)
{
	t_assign_list	*temp;
	char			*variable;
	int				i;
	int				j;
	int				k;
	char			*new_text;

	temp = list;
	i = 0;
	j = 0;
	k = 0;
	new_text = malloc(sizeof(char) * 2048);
	while (ast->token->value[i])
	{
		if (ast->token->value[i] == '$')
		{
			variable = get_variable(ast->token->value, &i);
			while (temp)
			{
				if (ft_strcmp(variable, temp->variable) == 0)
				{
					while (temp->value[j])
					{
						new_text[k] = temp->value[j];
						j++;
						k++;
					}
					*flag = 1;
					j = 0;
					break ;
				}
				temp = temp->next;
			}
			temp = list;
		}
		new_text[k] = ast->token->value[i];
		k++;
		i++;
	}
	ast->token->value = new_text;
}

void	ft_dollar(t_ast *ast, t_assign_list *list)
{
	int	flag;
	int	len;

	flag = 0;
	len = 0;
	if (ast == NULL)
		return ;
	if (ft_check_dollar(ast->token->value) && ast->token->value[0] != '\'')
	{
		if (!list)
			ast->token->value = remove_dollar(ast);
		else if (list)
		{
			ft_dollar_list(ast, list, &flag);
			if (flag == 0)
				ast->token->value = remove_dollar(ast);
		}
	}
	ft_dollar(ast->left, list);
	ft_dollar(ast->right, list);
}
