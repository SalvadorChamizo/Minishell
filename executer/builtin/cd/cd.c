/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:17:29 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/08 12:11:43 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

bool	cd_absolute(t_ast *tree, char *path, char **env)
{
	int	i;

	i = 0;
	if (access(tree->left->token->value, F_OK) < 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(tree->left->token->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (false);
	}
	else if (access(tree->left->token->value, X_OK) < 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(tree->left->token->value, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (false);
	}
	oldpwd_update(env);
	chdir(path);
	pwd_update(env);
	return (true);
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

bool	cd_relative(t_ast *tree, char *rout, char **env)
{
	char	**path;
	int		i;

	i = 0;
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
		return (false);
	}
	oldpwd_update(env);
	while (path[i])
	{
		ft_chdir(path[i], env);
		free(path[i]);
		i++;
	}
	free(path);
	return (true);
}

void	ft_cd(t_ast *tree, char **env, t_minishell *minishell)
{
	char	**path;

	path = NULL;
	if (tree->left)
		path = ft_split(tree->left->token->value, '/');
	else
	{
		minishell->status = 0;
		if (!cd_home(env))
			minishell->status = 1;
		return ;
	}
	if (tree->left->token->value[0] == '/')
	{
		minishell->status = 0;
		if (!cd_absolute(tree, tree->left->token->value, env))
			minishell->status = 1;
	}
	else
	{
		minishell->status = 0;
		if (!cd_relative(tree, tree->left->token->value, env))
			minishell->status = 1;
	}
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
