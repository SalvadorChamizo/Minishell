/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:56:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/21 23:16:04 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bash.h"

//GLOBAL
int		g_command_sig;

void	ft_do_line(t_minishell *minishell)
{
	minishell->input->pos = 0;
	minishell->ast = ft_expr(minishell->input);
	print_ast(minishell->ast);
	ft_expanser(minishell, minishell->env);
	ft_executer(minishell->ast, minishell);
	dup2(minishell->stdin_fd, STDIN_FILENO);
	dup2(minishell->stdout_fd, STDOUT_FILENO);
	free_ast(&minishell->ast);
	if (minishell->pipe_num != 0)
		free(minishell->store_fds);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_signal);
	minishell = minishell_init(env);
	while (1)
	{
		g_command_sig = 0;
		minishell->input = malloc(sizeof(t_input));
		if (input_init(minishell->input, minishell) == 1)
		{
			//ft_close();
			exit(0);
		}
		if (minishell->input->line[0] != '\0')
			add_history(minishell->input->line);
		minishell->input->line = ft_expand_heredoc(minishell->input->line, minishell);
		minishell->line_number++;
		minishell->input->pos = 0;
		if (ft_parser_fda(minishell) == 1)
			ft_do_line(minishell);
		free(minishell->input->line);
		free(minishell->input);
	}
	return (0);
}
