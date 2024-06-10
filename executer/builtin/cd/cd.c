/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:17:29 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/10 18:02:36 by saroca-f         ###   ########.fr       */
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

void	ft_cd(t_ast *tree, char **env, t_minishell *minishell)
{
	if (!tree->left)
	{
		minishell->status = 0;
		if (!cd_home(env))
			minishell->status = 1;
		return ;
	}
	if (tree->left->left)
	{
		minishell->status = 1;
		printf("bash: cd: too many arguments\n");
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
		if (!cd_relative(tree->left->token->value, env))
			minishell->status = 1;
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
