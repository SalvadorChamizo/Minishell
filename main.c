/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:56:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/31 18:47:16 by schamizo         ###   ########.fr       */
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
	t_ast				*syntax;
	int i;

	i = 0;
	(void)argc;
	(void)argv;
	signal(SIGINT, signal_c);
	signal(SIGQUIT, SIG_IGN);
	ft_enter(); //eslogan de entrada
	//execve("/usr/bin/bash", path, env);
	minishell = malloc(sizeof(t_minishell));
	if (minishell == NULL)
		return (1);
	minishell->list = NULL;
	ft_store_env(&minishell->list, env);
	while (1)
	{
		minishell->input = malloc(sizeof(t_input)); 
		if (input_init(minishell->input) == 1)
		{
			ft_exit();
			ft_list_clear(&minishell->list);
			free(minishell);
			exit(0);
		}
		if (minishell->input->line[0] != '\0')
			add_history(minishell->input->line);
		if (!ft_strncmp(minishell->input->line, "exit", 4))
        {
            ft_exit(); // eslogan de salida
            break;
        }
		else
		{
			minishell->input->pos = 0;
			syntax = ft_expr(minishell->input);
			ft_expanser(syntax, minishell, env);
			ft_executer(syntax, &env, &minishell->list);
			//print_ast(syntax);
			free(minishell->input->line);
			free_ast(&syntax);
		}
		free(minishell->input);
	}
	rl_clear_history();
	if (minishell->list)
		ft_list_clear(&minishell->list);
	free(minishell->input->line);
	free(minishell->input);
	free(minishell);
	return (0);
}
