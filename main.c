/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:56:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/24 12:38:01 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bash.h"

void	input_init(t_input *input, char **ev)
{
	int	i;

	i = 0;
	input->pos = 0;
	input->line = readline(RED"minishell> "RESET);
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
	while (1)
	{
		input = malloc(sizeof(t_input));
		input_init(input, env);
		add_history(input->line);
		if (!ft_strncmp(input->line, "exit", 4))
		{
			ft_exit(); //eslogan de salida
			break ;
		}
		else
		{
			input->pos = 0;
			syntax = ft_expr(input);
			/* print_ast(syntax);
			printf("\n\n"); */
			ft_expanser(syntax);
			print_ast(syntax);
			free(input->line);
		}
		free(input);
	}
	return (0);
}
