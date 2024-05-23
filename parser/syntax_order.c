/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:45:46 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/06 15:33:23 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_syntax	*find_last_lw(t_syntax *last_w)
{
	while (last_w->left)
		last_w = last_w->left;
	printf("\n"RED"%s\n"RESET, last_w->token->value);
	return (last_w);
}

void	find_last_rw(t_syntax *tree, t_syntax *third_rw)
{
	int			i;
	t_syntax	*second;

	printf(YELLOW"ENTRA"RESET);
	third_rw = tree;
	second = NULL;
	i = 0;
	while (third_rw->left && i != 2)
	{
		if (i == 1)
			second = third_rw;
		third_rw = third_rw->left;
		i++;
	}
	if (i < 2)
		third_rw = NULL;
	else
		second->left = NULL;
	printf("\n"GREEN"%s\n"RESET, third_rw->token->value);
}

t_syntax	*first_step(t_syntax *tree)
{
	t_syntax	*last_lw;
	t_syntax	*third_rw;

	printf(BLUE"ENTRA"RESET);
	last_lw = tree;
	third_rw = NULL;
	if (tree)
		find_last_rw(first_step(tree->right), find_last_lw(last_lw));
	last_lw->left = third_rw;
	return (tree);
}

t_syntax	*ft_order(t_syntax *syntax)
{
	t_syntax	*tree;

	tree = syntax;
	printf(RED"ENTRA"RESET);
	if (!tree)
		return (syntax);
	first_step(tree);
	return (syntax);
}
