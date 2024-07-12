/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:29:31 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/10 16:42:25 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	**ft_get_path(char **envp)
{
	int		i;
	int		flag;
	char	*str;
	char	**split;

	i = 0;
	flag = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
	{
		i++;
		if (envp[i] && ft_strncmp(envp[i], "PATH=", 5) == 0)
			flag = 1;
	}
	if (flag == 0)
		return (NULL);
	str = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	split = ft_split(str, ':');
	free(str);
	return (split);
}

void	expand_builtin(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->type == N_IDENTIFIER && check_builtin(ast->token->value))
		ast->type = N_BUILTIN;
	expand_builtin(ast->left);
	expand_builtin(ast->right);
}
