/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:47:13 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/26 17:44:22 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int		free_ast(t_ast **ast, int num)
{
	t_ast	*temp;
	char	*number;
	char	*filename;

	temp = *ast;
	if (temp == NULL)
		return (num);
	if (temp->type == N_HEREDOC)
	{
		number = ft_itoa(num);
		filename = ft_strjoin(".heredoc_tmp", number);
		unlink(filename);
		free(filename);
		free(number);
		num++;
	}
	num = free_ast(&temp->left, num);
	num = free_ast(&temp->right, num);
	free(temp->token->value);
	free(temp->token);
	free(temp);
	ast = NULL;
	return (num);
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
