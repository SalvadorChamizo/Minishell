/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:17:29 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/07 11:07:09 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bash.h"

void	cd_absolute(t_ast *tree, char **path, int i, char **env)
{
	if (access(tree->left->token->value, F_OK) < 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(tree->left->token->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	else if (access(tree->left->token->value, X_OK) < 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(tree->left->token->value, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return ;
	}
	oldpwd_update(env);
	regret_basic();
	while (path[i])
	{
		ft_chdir(path[i], env);
		i++;
	}
}

int	cd_relative_checker(t_ast *tree, char *rout)
{
	char	*wish;
	char	*now;
	
	now = getcwd(NULL, 0);
	wish = wish_ensambler(now, rout);
	free(now);
	if (access(tree->left->token->value, F_OK) < 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(tree->left->token->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(wish);
		return (0);
	}
	else if (access(tree->left->token->value, X_OK) < 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(tree->left->token->value, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(wish);
		return (0);
	}
	free(wish);
	return (1);
}

void cd_relative(t_ast *tree, char *rout, int i, char **env)
{
	char	**path;

	path = ft_split(rout, '/');
	if (!cd_relative_checker(tree, rout))
	{
		while (path[i])
		{
			ft_chdir(path[i], env);
			free(path[i]);
			i++;
		}
		free(path);
		return ;
	}
	oldpwd_update(env);
	while (path[i])
	{
		ft_chdir(path[i], env);
		free(path[i]);
		i++;
	}
	free(path);
}

void	ft_cd(t_ast *tree, char **env)
{
	char	**path;
	int		i;

	path = NULL;
	i = 0;
	if (tree->left)
		path = ft_split(tree->left->token->value, '/');
	else
	{
		oldpwd_update(env);
		gotouser(env);
		return ;
	}
	i = 0;
	if (tree->left->token->value[0] == '/')
		cd_absolute(tree, path, i, env);
	else
		cd_relative(tree, tree->left->token->value, i, env);
	ft_freepath(path);
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
