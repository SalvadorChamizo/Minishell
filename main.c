/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:56:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/06 15:32:40 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bash.h"

volatile sig_atomic_t g_signal = 0;

int	input_init(t_input *input)
{
	input->pos = 0;
	input->error = 0;
	input->line = readline(RED"minishell> "RESET);
	if (input->line == NULL && isatty(STDIN_FILENO)) // Detectar Ctrl+D cuando es interactivo
	{
		printf("exit\n");
		free(input->line);
		free(input);
		return (1);
	}
	return (0);
}


int	main(int argc, char **argv, char **env)
{
	t_minishell			*minishell;
	int		original_stdin;
	int		original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	(void)argc;
	(void)argv;
	disable_signal();
	signal(SIGINT, signal_c);
	signal(SIGQUIT, signal_slach);
	ft_enter();
	//execve("/usr/bin/bash", path, env);
	minishell = malloc(sizeof(t_minishell));
	if (minishell == NULL)
		return (1);
	minishell->list = NULL;
	ft_store_env(&minishell->list, env);
	minishell->env = env;
	minishell->line_number = 0;
	minishell->status = 0;
	while (1)
	{
		minishell->input = malloc(sizeof(t_input)); 
		if (input_init(minishell->input) == 1)
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
			ft_expanser(minishell, env);
			ft_executer(minishell->ast, minishell);
			dup2(original_stdin, STDIN_FILENO);
			dup2(original_stdout, STDOUT_FILENO);
			free_ast(&minishell->ast);
		}
		free(minishell->input->line);
		free(minishell->input);
	}
	return (0);
}
