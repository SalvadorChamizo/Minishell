/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:47:13 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/28 16:52:31 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	free_ast(t_ast **ast)
{
	if (*ast == NULL)
		return ;
	free_ast(&(*ast)->left);
	free_ast(&(*ast)->right);
	free((*ast)->token);
	free(*ast);
	ast = NULL;
}