/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_directory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:31:17 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/16 20:33:50 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

bool is_command(const char *path)
{
	struct stat path_stat;
    
    if (stat(path, &path_stat) != 0)
        return (false);
    if ((path_stat.st_mode & S_IFMT) == S_IFREG && (path_stat.st_mode & S_IXUSR))
        return (true);
    return (false);
}

bool	ft_expanser_directory(t_ast *ast)
{
	if (!ft_strchr(ast->token->value, '/'))
		return (false);
	if (is_command(ast->token->value))
		return (false);
	return (true);
}
