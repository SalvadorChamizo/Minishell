/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:42:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/31 12:47:11 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void    ft_unset(t_ast *ast, t_assign_list **list)
{
	t_ast 			*temp;
	t_assign_list	*templ;
	t_assign_list	*templ2;

	temp = ast->left;
	while (temp)
	{
		templ = *list;
		while(templ)
		{
			if (!ft_strcmp(templ->variable, temp->token->value))
			{
				free(templ->variable);
				free(templ->value);
				if (templ == *list)
					*list = templ->next;
				else
					templ2->next = templ->next;
				free (templ);
			}
			if (templ != *list)
				templ2 = templ;
			templ = templ->next;
		}
		temp = temp->left;
	}
}
