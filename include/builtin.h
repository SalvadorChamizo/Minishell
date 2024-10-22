/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:52:31 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/09 13:38:18 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "structs.h"

//Builtin
	//CD
void		ft_cd(t_ast *tree, char **env, t_minishell *minishell);
bool		cd_home(char **env);
bool		cd_hyphen(char **env);
void		cd_relative(char *rout, char **env, t_minishell *minishell);
void		cd_error(char *path);
void		point_maker(char **point, char *step);
void		ft_cd_free_mat(char **path);
int			ft_chdir(char *order, char **env);
void		oldpwd_update(char **env);
void		pwd_update(char **env);
	//PWD
void		ft_pwd(t_minishell *minishell, char **env);
	//ECHO
void		ft_echo(t_ast *ast, t_minishell *minishell);
	//ENV
void		ft_env(t_ast *ast, t_minishell *minishell);
	//EXPORT
void		ft_export(t_ast *ast, t_minishell *minishell);
void		ft_export_addiction(char *str, char **env);
void		new_env_manager(char *str, char **newenv);
int			var_len(char *str);
void		export_print(char **env);
void		ft_putenv_fd(char *s);
bool		identifier_check(char *str);
char		*export_str_builder(t_ast **tmp);
	//UNSET
void		ft_unset(t_ast *ast, t_minishell *minishell);
void		ft_exit(t_minishell **minishell, t_ast *ast);

#endif
