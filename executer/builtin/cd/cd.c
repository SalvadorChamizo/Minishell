/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:17:29 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/09 11:10:19 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

void	cd_absolute(t_ast *tree, char *path, char **env, t_minishell *minishell)
{
	minishell->status = 0;
	if (access(tree->left->token->value, F_OK) < 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(tree->left->token->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		minishell->status = 1;
		return ;
	}
	else if (access(tree->left->token->value, X_OK) < 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(tree->left->token->value, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		minishell->status = 1;
		return ;
	}
	oldpwd_update(env);
	chdir(path);
	pwd_update(env);
}

void	ft_cd(t_ast *tree, char **env, t_minishell *minishell)
{
	if (!tree->left)
	{
		minishell->status = 0;
		if (!cd_home(env))
			minishell->status = 1;
		return ;
	}
	else if (tree->left->left)
	{
		minishell->status = 1;
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		return ;
	}
	else if (ft_strcmp(tree->left->token->value, "-") == 0)
	{
		minishell->status = 0;
		if (!cd_hyphen(env))
			minishell->status = 1;
		return ;
	}
	else if (tree->left->token->value[0] == '/')
		cd_absolute(tree, tree->left->token->value, env, minishell);
	else
		cd_relative(tree->left->token->value, env, minishell);
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
