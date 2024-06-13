/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:47:13 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/07 15:23:59 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	free_ast(t_ast **ast)
{
	t_ast	*temp;

	temp = *ast;
	if (temp == NULL)
		return ;
	free_ast(&temp->left);
	free_ast(&temp->right);
	free(temp->token->value);
	free(temp->token);
	free(temp);
	ast = NULL;
}

void	*free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

void	ft_list_clear(t_assign **list)
{
	t_assign	*temp;

	if (!list)
		return ;
	while (*list)
	{
		free((*list)->value);
		free((*list)->variable);
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
	*list = NULL;
}
