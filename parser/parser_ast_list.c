/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:58:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/25 12:07:57 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	ft_add_identifier_front(t_idenlst **lst, t_idenlst *new)
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	ft_lstadd_identifier(t_idenlst **lst, t_idenlst *new)
{
	t_idenlst	*last;

	last = *lst;
	if (!last)
		*lst = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
}

t_idenlst	*ft_lstnew_identifier(t_token *token)
{
	t_idenlst	*new;

	new = NULL;
	new = malloc(sizeof(t_idenlst));
	if (!new)
		return (NULL);
	if (new)
	{
		new->token = token;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}
