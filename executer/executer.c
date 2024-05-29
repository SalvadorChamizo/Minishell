/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:47:22 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/29 18:25:52 by schamizo         ###   ########.fr       */
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

/*void    ft_command(t_ast *ast)
{
    if (ast->right)
    {
        ft_pipeline(ast->right);
    }
}*/

void    ft_pipeline(t_ast *ast, char **env)
{
    if (ast->type == N_PIPELINE)
    {
        ft_pipeline(ast->left, env);
        ft_pipeline(ast->right, env);
    }
    if (ast->type == N_HEREDOC || ast->type == N_REDIRECTION)
    {

    }
    if (ast->type == N_COMMAND)
    {
        //ft_command(ast);
    }
    if (ast->type == N_BUILTIN)
    {
        execute_builtin(ast, env);
    }
}


void    ft_executer(t_ast *ast, char **env)
{
    if (ast->type == N_PIPELINE)
    {
        ft_pipeline(ast->left, env);
        ft_pipeline(ast->right, env);
    }
    if (ast->type == N_BUILTIN)
        execute_builtin(ast, env);
    //if (ast->type == N_COMMAND)
        //ft_command(ast);
}