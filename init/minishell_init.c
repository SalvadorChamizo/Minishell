/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:02:48 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/09 19:23:44 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	input_init(t_input *input)
{
	char	*user;
	char	*computer;

	input->pos = 0;
	input->error = 0;
	input->line = NULL;
	user = getenv("USER");
	computer = getenv("SESSION_MANAGER");
	computer = ft_substr(computer, 6, 6);
	printf(RED"%s@%s", user, computer);
	input->line = readline(RED"> "RESET);
	if (input->line == NULL && isatty(STDIN_FILENO)) // Detectar Ctrl+D cuando es interactivo
	{
		printf("exit\n");
		free(input->line);
		free(input);
		return (1);
	}
	free(computer);
	return (0);
}

char	**ft_env_init(char **env)
{
	char	**newenv;
	int		i;
	int		j;

	j = 0;
	while (env[j])
		j++;
	newenv = NULL;
	newenv = malloc(sizeof(char *) * (j + 1));
	i = 0;
	while (env[i])
	{
		newenv[i] = ft_strdup(env[i]);
		i++;
	}
	newenv[i] = NULL;
	return (newenv);
}

t_minishell	*minishell_init(char **env)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (minishell == NULL)
		return (NULL);
	minishell->env = NULL;
	minishell->env = ft_env_init(env);
	minishell->list = NULL;
	ft_store_env(&minishell->list, env);
	minishell->line_number = 0;
	minishell->status = 0;
	minishell->stdin_fd = dup(STDIN_FILENO);
	minishell->stdout_fd = dup(STDOUT_FILENO);
	return (minishell);
}
