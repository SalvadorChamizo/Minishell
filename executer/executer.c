/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:47:22 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/29 16:10:23 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	execute_builtin(t_ast *ast, char ***env)
{
    if (!ft_strcmp(ast->token->value, "cd"))
        ft_cd(ast, *env);
    else if (!ft_strcmp(ast->token->value, "pwd"))
        ft_pwd();
    else if (!ft_strcmp(ast->token->value, "echo"))
        ft_echo(ast);
    else if (!ft_strcmp(ast->token->value, "env"))
        ft_env(*env);
    else if (!ft_strcmp(ast->token->value, "export"))
        ft_export(ast, env);
    /*else if (!ft_strcmp(ast->token->value, "unset"))
        ft_unset(ast->right);
    else if (!ft_strcmp(ast->token->value, "exit"))
        ft_exit(ast->right);*/
}
void    ft_executer(t_ast *ast, char ***env)
{
    execute_builtin(ast, env);
}