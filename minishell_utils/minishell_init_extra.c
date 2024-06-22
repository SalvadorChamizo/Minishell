/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:22:24 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/22 15:21:39 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

/*void	make_new_line(char **new_line, int i, int j, t_minishell *minishell)
{
	if (j == i)
	{
		only_dollar(new_line, i, j, minishell);
		return ;
	}
}

void	dollar_line(char *line, t_minishell *minishell)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	new_line = ft_strdup(line);
	while (new_line[i])
	{
		if (new_line[i] == '$')
		{
			j = i;
			while (new_line[j] != ' ' && new_line[j] != '\0' && new_line[j] != '\"' && new_line[j] != '\'' && new_line[j] != '(')
				j++;
			make_new_line(&new_line, i, j, minishell);
		}
		i++;
	}
}*/

void	init_variables(t_input *input, t_minishell *minishell)
{
	signal(SIGQUIT, SIG_IGN);
	input->pos = 0;
	input->error = 0;
	input->line = NULL;
	minishell->pipe_check = 0;
	minishell->infile_check = -1;
	minishell->outfile_check = -1;
	minishell->pipe_num = 0;
}
