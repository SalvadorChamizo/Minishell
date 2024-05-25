/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:56:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/25 10:47:19 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bash.h"

///////////////////////////////////////////

volatile sig_atomic_t sigint_received = 0;

void signal_c(int signal_number) 
{
	if (signal_number == SIGINT)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			sigint_received = 1;
		}
		else
		{
			sigint_received = 1;
		}
	}
}

//////////////////////////////////////////

void	input_init(t_input *input, char **ev)
{
	int	i;

	i = 0;
	input->pos = 0;
	input->line = readline(RED"minishell> "RESET);
	if (input->line == NULL && isatty(STDIN_FILENO)) // Detectar Ctrl+D cuando es interactivo
	{
		printf("exit\n");
		exit(0);
	}
	while (ev[i] != NULL)
	{
		if (ft_strcmp(ev[i], "PATH="))
		{
			input->path = ft_split(ev[i], ':');
			break ;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_input				*input;
	t_ast				*syntax;

	(void)argc;
	(void)argv;
	ft_enter(); //eslogan de entrada
	signal(SIGINT, signal_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = malloc(sizeof(t_input));
		input_init(input, env);
		add_history(input->line);
		/*if (sigint_received) 
		{
			sigint_received = 0;
			free(input->line);
        }*/
		 if (!strncmp(input->line, "exit", 4)) 
        {
            ft_exit(); // eslogan de salida
            break;
        }
		else
		{
			input->pos = 0;
			syntax = ft_expr(input);
			ft_expanser(syntax);
			print_ast(syntax);
			free(input->line);
		}
		free(input);
	}
	return (0);
}
