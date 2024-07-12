/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:42:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/12 18:00:16 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

void	list_case(t_assign **list, char *str)
{
	t_assign	*templ;
	t_assign	*templ2;

	templ = *list;
	while (templ)
	{
		if (!ft_strcmp(templ->variable, str))
		{
			free(templ->variable);
			free(templ->value);
			if (templ == *list)
				*list = templ->next;
			else
				templ2->next = templ->next;
			free (templ);
			return ;
		}
		templ2 = templ;
		templ = templ->next;
	}
}

void	env_case(char ***env, char *str)
{
	int		i;

	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], str, ft_strlen(str)))
		{
			free((*env)[i]);
			while ((*env)[i + 1])
			{
				(*env)[i] = (*env)[i + 1];
				i++;
			}
			(*env)[i] = NULL;
			free((*env)[i + 1]);
		}
		i++;
	}
}

void	ft_unset(t_ast *ast, t_minishell *minishell)
{
	t_ast			*temp;

	temp = ast->left;
	while (temp)
	{
		list_case(&minishell->list, temp->token->value);
		env_case (&minishell->env, temp->token->value);
		temp = temp->left;
	}
	minishell->status = 0;
}
