/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:02:48 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/10 10:17:28 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	*readline_prompt(void)
{
	char	*computer;
	char	*prompt;
	char	*ret;
	char	*ret2;

	prompt_init(&computer, &prompt, &ret, &ret2);
	computer = getenv("USER");
	if (!computer)
		return (NULL);
	ret = ft_strjoin(computer, "@");
	computer = getenv("SESSION_MANAGER");
	if (!computer)
		return (NULL);
	ret2 = ft_substr(computer, 6, 6);
	computer = ft_strjoin(ret, ret2);
	free(ret);
	free(ret2);
	ret = ft_strjoin(computer, "> ");
	free(computer);
	ret2 = ft_strjoin("\001"RED"\002", ret);
	free(ret);
	prompt = ft_strjoin(ret2, "\001"RESET"\002");
	free(ret2);
	return (prompt);
}

int	input_init(t_input *input, t_minishell *minishell)
{
	char	*prompt;

	init_variables(input, minishell);
	prompt = readline_prompt();
	if (prompt)
		input->line = readline(prompt);
	else
		input->line = readline(RED"minishell> "RESET);
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

char	**ft_null_env(void)
{
	char	**env;
	char	*path;

	env = malloc(sizeof(char *) * 5);
	if (!env)
		exit(1);
	path = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:");
	env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strjoin(path, "/usr/sbin:/usr/bin:/sbin:/bin");
	env[3] = ft_strdup("_=/usr/bin/env");
	env[4] = NULL;
	free(path);
	return (env);
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
	if (env[0])
		minishell->env = ft_env_init(env);
	else
		minishell->env = ft_null_env();
	minishell->underscore = NULL;
	minishell->list = NULL;
	ft_store_env(&minishell->list, minishell->env);
	minishell->line_number = 0;
	minishell->status = 0;
	minishell->stdin_fd = dup(STDIN_FILENO);
	minishell->stdout_fd = dup(STDOUT_FILENO);
	return (minishell);
}
