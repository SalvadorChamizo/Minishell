/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:12:02 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/29 18:25:08 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	mat_extenser(char **env)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	return (i);
}

void	ft_newenv(char ***env, char *str)
{
	int		i;
	char	**newenv;

	i = mat_extenser(*env) + 2;
	newenv = malloc(sizeof(char *) * i);
	i = 0;
	while((*env)[i])
	{
		newenv[i] = (*env)[i];
		i++;
	}
	newenv[i] = malloc(sizeof(char) * ft_strlen(str) + 1);
	strcpy(newenv[i], str);
	printf("[%d]"YELLOW" (%s)"RESET" se asigna\n", i, newenv[i]);
	newenv[i + 1] = NULL;
	*env = newenv;
}

/*void	ft_export(t_ast *ast, char ***env)
{
	t_ast	*tmp;
	int		i;

	tmp = ast->left;
	i = 0;
	if (!tmp)
	{
		while ((*env)[i] != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd((*env)[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
		return ;
	}
	while (tmp)
	{
		ft_newenv(env, tmp->token->value);
		tmp = tmp->left;
	}
}*/
