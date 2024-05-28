/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:04:59 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/28 12:29:57 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	ft_echo(t_ast *ast)
{
    t_ast *tmp;

    tmp = ast->left;
    while (tmp)
    {
        if (ft_strcmp(tmp->token->value, ""))
            ft_putstr_fd(tmp->token->value, 1);
        else
            ft_putstr_fd("", 1);
        if (tmp->left)
            ft_putstr_fd(" ", 1);
        tmp = tmp->left;
    }
    ft_putstr_fd("\n", 1);
}
