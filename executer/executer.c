/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:47:22 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/28 10:39:15 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	execute_builtin(t_ast *ast)
{
    if (!ft_strcmp(ast->token->value, "cd"))
        ft_cd(ast);
    else if (!ft_strcmp(ast->token->value, "pwd"))
        ft_pwd();
    /*else if (!ft_strcmp(ast->token->value, "echo"))
        ft_echo(ast->right);
    else if (!ft_strcmp(ast->token->value, "export"))
        ft_export(ast->right);
    else if (!ft_strcmp(ast->token->value, "unset"))
        ft_unset(ast->right);
    else if (!ft_strcmp(ast->token->value, "env"))
        ft_env();
    else if (!ft_strcmp(ast->token->value, "exit"))
        ft_exit(ast->right);*/
}
void    ft_executer(t_ast *ast)
{
    execute_builtin(ast);
}