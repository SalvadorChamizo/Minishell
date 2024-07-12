/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:22:24 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/10 10:17:02 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	prompt_init(char **computer, char **prompt, char **ret, char **ret2)
{
	*computer = NULL;
	*ret = NULL;
	*prompt = NULL;
	*ret2 = NULL;
}

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
