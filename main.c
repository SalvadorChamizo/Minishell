/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:56:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/25 15:56:25 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bash.h"

void	input_init(t_input *input, char **ev)
{
	int	i;

	i = 0;
	input->pos = 0;
	input->line = readline(RED"minishell> "RESET);
	//input->line = "echo \"$hola     pero    $y\"";
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
	t_minishell			*minishell;
	t_ast				*syntax;
	//char				**path = NULL;

	(void)argc;
	(void)argv;
	ft_enter(); //eslogan de entrada
	//execve("/usr/bin/bash", path, env);
	minishell = malloc(sizeof(t_minishell));
	while (1)
	{
		minishell->input = malloc(sizeof(t_input)); 
		input_init(minishell->input, env);
		add_history(minishell->input->line);
		if (!ft_strncmp(minishell->input->line, "exit", 4))
		{
			ft_exit(); //eslogan de salida
			break ;
		}
		else
		{
			minishell->input->pos = 0;
			syntax = ft_expr(minishell->input);
			/* print_ast(syntax);
			printf("\n\n"); */
			ft_expanser(syntax , minishell);
			print_ast(syntax);
			free(minishell->input->line);
		}
		free(minishell->input);
	}
	return (0);
}
