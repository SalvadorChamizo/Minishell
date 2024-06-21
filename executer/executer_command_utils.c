/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:08:34 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/13 18:10:34 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	*ft_remove_path(char *command)
{
	char	*new_text;
	int		i;
	int		len;

	i = 0;
	if (command[i] != '/')
	{
		new_text = ft_strdup(command);
		return (new_text);
	}
	while (command[i])
		i++;
	len = i;
	while (command[i] != '/')
		i--;
	i++;
	len = len - i;
	new_text = ft_substr(command, i, len);
	return (new_text);
}

char	**ft_command_args_aux(t_ast *temp, char **args)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (temp->token->value != NULL
			&& ft_strcmp(temp->token->value, "") != 0)
		{
			if (i == 0)
				args[i] = ft_remove_path(temp->token->value);
			else
				args[i] = temp->token->value;
		}
		temp = temp->left;
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	**ft_command_args(t_ast *ast)
{
	t_ast	*temp;
	char	**args;
	int		i;

	temp = ast;
	i = 1;
	while (temp)
	{
		temp = temp->left;
		i++;
	}
	temp = ast;
	args = malloc(sizeof(char *) * i);
	ft_command_args_aux(temp, args);
	return (args);
}

int	ft_check_path(char **envp)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
	{
		i++;
		if (envp[i] && ft_strncmp(envp[i], "PATH=", 5) == 0)
			flag = 1;
	}
	if (flag == 0)
		return (0);
	return (1);
}