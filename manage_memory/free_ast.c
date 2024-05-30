/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:47:13 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/29 11:50:58 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	free_ast(t_ast **ast)
{
	if (*ast == NULL)
		return ;
	free_ast(&(*ast)->left);
	free_ast(&(*ast)->right);
	free((*ast)->token->value);
	free((*ast)->token);
	free(*ast);
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