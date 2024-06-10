/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:56:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/10 12:13:49 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bash.h"

//GLOBAL
int		command_sig;

//PROGRAM
int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	int			original_stdin;
	int			original_stdout;

	command_sig = 0;
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_signal);
	ft_enter();
	//execve("/usr/bin/bash", path, env);
	minishell = minishell_init(env);
	while (1)
	{
		minishell->input = malloc(sizeof(t_input));
		if (input_init(minishell->input) == 130)
		{
			ft_close();
			ft_list_clear(&minishell->list);
			free(minishell);
			exit(0);
		}
		if (minishell->input->line[0] != '\0')
			add_history(minishell->input->line);
		minishell->line_number++;
		minishell->input->pos = 0;
		if (ft_parser_fda(minishell->input) == 1)
		{
			minishell->input->pos = 0;
			minishell->ast = ft_expr(minishell->input);
			//print_ast(minishell->ast);
			ft_expanser(minishell, minishell->env);
			//print_ast(minishell->ast);
			ft_executer(minishell->ast, minishell);
			//print_ast(minishell->ast);
			dup2(original_stdin, STDIN_FILENO);
			dup2(original_stdout, STDOUT_FILENO);
			free_ast(&minishell->ast);
		}
		free(minishell->input->line);
		free(minishell->input);
	}
	return (0);
}
