/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:08:34 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/10 09:34:57 by schamizo         ###   ########.fr       */
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

char	*command_args_builder(t_ast **tmp)
{
	char	*str;
	char	*tep;

	str = ft_strdup((*tmp)->token->value);
	tep = NULL;
	while ((*tmp)->left && (*tmp)->left->token->space == false)
	{
		(*tmp) = (*tmp)->left;
		tep = ft_strjoin(str, (*tmp)->token->value);
		free(str);
		str = tep;
	}
	return (str);
}

char	**ft_command_args_aux(t_ast *temp, char **args)
{
	int	i;

	i = 0;
	while (temp)
	{
		args[i] = command_args_builder(&temp);
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
		while (temp && temp->token->space == true)
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
