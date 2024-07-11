/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:56:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/11 12:15:46 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bash.h"

//GLOBAL
int		g_command_sig;

void	ft_underscore_asg(t_minishell *minishell)
{
	int	ret;
	char *str;

	ret = 0;
	str = NULL;
	if (!minishell->underscore)
		return ;
	while (minishell->env[ret])
	{
		if (!ft_strncmp(minishell->env[ret], "_=", 2))
			break ;
		ret++;
	}
	if (!minishell->env[ret] || !ft_strncmp(minishell->underscore, "$_", 2))
		return ;
	free(minishell->env[ret]);
	str = ft_strjoin("_=", minishell->underscore);
	minishell->env[ret] = ft_strdup(str);
	free(str);
}

void	ft_do_line(t_minishell *minishell)
{
	minishell->input->pos = 0;
	minishell->ast = ft_parser_ast(minishell->input);
	//print_ast(minishell->ast);
	ft_expander(minishell, minishell->env);
	//print_ast(minishell->ast);
	ft_executer(minishell->ast, minishell);
	ft_underscore_asg(minishell);
	dup2(minishell->stdin_fd, STDIN_FILENO);
	dup2(minishell->stdout_fd, STDOUT_FILENO);
	free_ast(&minishell->ast, 1);
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
		minishell->input->line = ft_expand_str(minishell->input->line, minishell);
		minishell->line_number++;
		minishell->input->pos = 0;
		if (ft_parser_fda(minishell) == 1)
			ft_do_line(minishell);
		free(minishell->input->line);
		free(minishell->input);
	}
	return (0);
}
