/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:02:48 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/13 15:22:02 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	*readline_prompt(void)
{
	char	*computer;
	char	*prompt;
	char	*ret;
	char	*ret2;

	computer = getenv("USER");
	ret = ft_strjoin(computer, "@");
	computer = getenv("SESSION_MANAGER");
	ret2 = ft_substr(computer, 6, 6);
	computer = ft_strjoin(ret, ret2);
	free(ret);
	free(ret2);
	ret = ft_strjoin(computer, "> ");
	free(computer);
	ret2 = ft_strjoin(RED"", ret);
	free(ret);
	prompt = ft_strjoin(ret2, ""RESET);
	free(ret2);
	return (prompt);
}

int	input_init(t_input *input, t_minishell *minishell)
{
	char	*prompt;

	signal(SIGQUIT, SIG_IGN);
	input->pos = 0;
	input->error = 0;
	input->line = NULL;
	minishell->pipe_check = 0;
	minishell->pipe_num = 0;
	prompt = readline_prompt();
	input->line = readline(prompt);
	if (input->line == NULL && isatty(STDIN_FILENO))
	{
		printf("exit\n");
		free(prompt);
		free(input->line);
		free(input);
		if (minishell->pipe_num != 0)
			free(minishell->store_fds);
		ft_list_clear(&minishell->list);
		free_split(minishell->env);
		free(minishell);
		return (1);
	}
	free(prompt);
	signal(SIGQUIT, quit_signal);
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

	ft_enter();
	minishell = malloc(sizeof(t_minishell));
	if (minishell == NULL)
		return (NULL);
	minishell->ast = NULL;
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
