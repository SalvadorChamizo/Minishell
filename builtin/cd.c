/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:17:29 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/27 15:57:09 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	cd_error(char *path)
{
	char	*wish;

	wish = ft_strjoin(getcwd(NULL, 0), path);
	if (access(wish, X_OK) == 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

void	regret_basic(t_ast *tree)
{
	while (ft_strcmp(getcwd(NULL, 0), "/") != 0)
	{
		if (chdir("..") == -1)
		{
			cd_error(tree->left->token->value);
			break ;
		}
	}
}

void	cd_complete_path(t_ast *tree, char **path, int i)
{
	regret_basic(tree);
	while (path[i])
	{
		if (chdir(path[i]) == -1)
			cd_error(tree->left->token->value);
		i++;
	}
}

void	ft_cd(t_ast *tree)
{
	char	**path;
	int		i;

	path = ft_split(tree->left->token->value, '/');
	i = 0;
	if (path[0] == NULL)
	{
		regret_basic(tree);
		if (chdir("home") == -1)
			cd_error(tree->left->token->value);
		if (chdir(getenv("USER")) == -1)
			cd_error(tree->left->token->value);
	}
	else if (tree->left->token->value[0] == '/')
		cd_complete_path(tree, path, i);
	else
	{
		while (path[i])
		{
			if (chdir(path[i]) == -1)
				cd_error(tree->left->token->value);
			i++;
		}
	}
}

/*int main()
{
	t_ast *tree;

	printf(RED"DIR actual: "MAGENTA"%s\n"RESET, getcwd(NULL, 0));
	while(1)
	{
		tree = malloc(sizeof(t_ast));
		tree->left = malloc(sizeof(t_ast));
		tree->left->token = malloc(sizeof(t_token));
		tree->left->token->value = readline("Enter the path: ");
		if (tree->left->token->value == NULL)
			break;
		ft_cd(tree);
		printf(RED"DIR actual: "MAGENTA"%s\n"RESET,getcwd(NULL, 0));
	}
	return (0);
}*/
