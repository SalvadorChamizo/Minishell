/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:42:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/05 15:33:24 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	list_case(t_assign_list **list, char *str)
{
	t_assign_list	*templ;
	t_assign_list	*templ2;

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

void	ft_unset(t_ast *ast, char ***env, t_assign_list **list)
{
	t_ast			*temp;

	temp = ast->left;
	if (env)
		;
	while (temp)
	{
		list_case(list, temp->token->value);
		env_case (env, temp->token->value);
		temp = temp->left;
	}
}
