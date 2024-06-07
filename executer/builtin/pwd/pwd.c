/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:37:46 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/07 15:27:37 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

void	ft_pwd(t_minishell *minishell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	minishell->status = 0;
}
