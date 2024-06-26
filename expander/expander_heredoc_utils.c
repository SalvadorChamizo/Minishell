/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:46:49 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/25 18:39:12 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	ft_store_heredoc(t_ast *ast, t_minishell *minishell, int num)
{
	char	*filename;
	char	*number;

	if (!ast)
		return (num);
	if (ast->type == N_HEREDOC)
	{
		number = ft_itoa(num);
		filename = ft_strjoin(".heredoc_tmp", number);
		printf("%s\n", filename);
		free(filename);
		free(number);
		num++;
	}
	num = ft_store_heredoc(ast->left, minishell, num);
	num = ft_store_heredoc(ast->right, minishell, num);
	return (num);
}
