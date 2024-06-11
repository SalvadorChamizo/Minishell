/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:56:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/11 18:29:09 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bash.h"

//GLOBAL
int		command_sig;

//PROGRAM
int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	command_sig = 0;
	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_signal);
	ft_enter();
	//execve("/usr/bin/bash", path, env);
	minishell = minishell_init(env);
	while (1)
	{
		minishell->input = malloc(sizeof(t_input));
		if (input_init(minishell->input, minishell) == 1)
		{
			ft_close();
			exit(130);
		}
		if (minishell->input->line[0] != '\0')
			add_history(minishell->input->line);
		minishell->line_number++;
		minishell->input->pos = 0;
		if (ft_parser_fda(minishell->input) == 1)
		{
			minishell->input->pos = 0;
			minishell->ast = ft_expr(minishell->input);
			print_ast(minishell->ast);
			ft_expanser(minishell, minishell->env);
			print_ast(minishell->ast);
			ft_executer(minishell->ast, minishell);
			dup2(minishell->stdin_fd, STDIN_FILENO);
			dup2(minishell->stdout_fd, STDOUT_FILENO);
			free_ast(&minishell->ast);
		}
		free(minishell->input->line);
		free(minishell->input);
	}
	return (0);
}
