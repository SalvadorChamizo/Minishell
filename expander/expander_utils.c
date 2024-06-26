/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:35:25 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/25 15:03:45 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	check_builtin(char *text)
{
	if (!ft_strcmp(text, "echo"))
		return (1);
	else if (!ft_strcmp(text, "cd"))
		return (1);
	else if (!ft_strcmp(text, "pwd"))
		return (1);
	else if (!ft_strcmp(text, "export"))
		return (1);
	else if (!ft_strcmp(text, "unset"))
		return (1);
	else if (!ft_strcmp(text, "env"))
		return (1);
	else if (!ft_strcmp(text, "exit"))
		return (1);
	return (0);
}

int	check_prev(t_ast *prev)
{
	if (prev->type != N_IDENTIFIER && prev->type != N_COMMAND
		&& prev->type != N_ARGUMENT)
		return (1);
	return (0);
}

int	check_prev2(t_ast *prev)
{
	if (prev->type == N_IDENTIFIER || prev->type == N_COMMAND
		|| prev->type == N_ARGUMENT)
		return (1);
	return (0);
}

int	check_equal(char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i] == '=' && i != 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_store_env(t_assign **list, char **envp)
{
	t_assign	*new_node;
	int			i;

	new_node = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = new_assignment(envp[i], *list);
		ft_assign_add_back(list, new_node);
		i++;
	}
}

char	*expand_quotes_str(char *str)
{
	char	*new_str;

	if (str == NULL)
		return (str);
	if (str[0] == '\"' || str[0] == '\'')
	{
		if (str[0] == '\"')
		{
			new_str = ft_strtrim(str, "\"");
			free(str);
			return (new_str);
		}
		else if (str[0] == '\'')
		{
			new_str = ft_strtrim(str, "\'");
			free(str);
			return (new_str);
		}
	}
	return (str);
}
