/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_assign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:40:29 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/22 10:15:57 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	get_new_value(char *value, char **new_value)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (value[i])
	{
		if (value[i] == '\'' && flag != 2)
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
			i++;
		}
		if (value[i] == '\"' && flag != 1)
		{
			if (flag == 0)
				flag = 2;
			else
				flag = 0;
			i++;
		}
		(*new_value)[j] = value[i];
		i++;
		j++;
	}
	(*new_value)[j] = '\0';
}

void	assigment_value(t_ast *ast)
{
	char	*value;
	char	*new_value;

	value = ast->token->value;
	new_value = malloc(sizeof(char) * new_value_size(value) + 1);
	if (!new_value)
		return ;
	get_new_value(value, &new_value);
	free(ast->token->value);
	ast->token->value = new_value;
}

void	expand_assignment(t_ast *ast, t_ast *prev)
{
	if (ast == NULL)
		return ;
	if (prev == NULL && check_equal(ast->token->value))
	{
		assigment_value(ast);
		ast->type = N_ASSIGN;
	}
	if (prev != NULL)
	{
		if (prev->type != N_COMMAND && prev->type != N_IDENTIFIER
			&& prev->type != N_ARGUMENT && check_equal(ast->token->value))
		{
			assigment_value(ast);
			ast->type = N_ASSIGN;
		}
	}
	expand_assignment(ast->left, ast);
	expand_assignment(ast->right, ast);
}

t_assign	*new_assignment(char *text, t_assign *list)
{
	t_assign	*new_node;
	t_assign	*temp;
	char		*word;
	char		*new_value;
	int			i;

	i = 0;
	while (text[i] != '=')
		i++;
	word = ft_substr(text, 0, i);
	if (list)
	{
		temp = list;
		while (temp)
		{
			if (!ft_strcmp(word, temp->variable))
			{
				new_value = ft_substr(text, i + 1, ft_strlen(text) - i);
				free(temp->value);
				free(word);
				temp->value = new_value;
				return (NULL);
			}
			temp = temp->next;
		}
	}
	new_node = malloc(sizeof(t_assign));
	new_node->variable = word;
	new_node->value = ft_substr(text, i + 1, ft_strlen(text) - i);
	new_node->next = NULL;
	return (new_node);
}

void	ft_assign_add_back(t_assign **lst, t_assign *new)
{
	t_assign	*last;

	last = *lst;
	if (!last)
		*lst = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	store_assignment(t_ast *ast, t_assign **list)
{
	t_assign	*new_node;

	new_node = NULL;
	if (ast == NULL || ast->token->type == T_PIPE
		|| ast->token->type == T_IDENTIFIER)
		return ;
	if (ast->type == N_ASSIGN)
	{
		new_node = new_assignment(ast->token->value, *list);
		ft_assign_add_back(list, new_node);
	}
	store_assignment(ast->left, list);
	store_assignment(ast->right, list);
}
