/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:53:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/12 13:02:19 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	*remove_dollar(t_ast *ast)
{
	char	*text;
	char	*new_text;
	int		i;
	int		j;

	text = ft_strdup(ast->token->value);
	free(ast->token->value);
	new_text = malloc(sizeof(char) * ft_strlen(text));
	i = 0;
	j = 0;
	while (text[i] != '\0')
	{
		if (text[i] == '$')
		{
			while (text[i] != ' ' && text[i] != '\0')
				i++;
		}
		new_text[j] = text[i];
		if (text[i] != '\0')
			i++;
		j++;
	}
	new_text[j] = '\0';
	free(text);
	return (new_text);
}

char	*get_variable(char	*text, int *cur)
{
	char	*variable;
	int		i;

	variable = NULL;
	i = *cur + 1;
	if (text[*cur] == '$')
	{
		while (text[*cur] != ' ' && text[*cur] != '\0' 
			&& text[*cur] != '\'' && text[*cur] != '\"')
			*cur = *cur + 1;
		variable = ft_substr(text, i, *cur - i);
	}
	return (variable);
}

void	ft_dollar_list(t_ast *ast, t_assign *list, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	t_assign	*temp;
	int				i;

	i = 0;
	dollar = malloc(sizeof(t_dollar));
	new_text = malloc(sizeof(char) * 2048);
	dollar->flag = flag;
	if (!ft_check_dollar(ast->token->value))
	{
		free(new_text);
		free(dollar);
		return ;
	}
	while (ast->token->value[i])
	{
		if (ast->token->value[i] == '$')
		{
			dollar->variable = get_variable(ast->token->value, &i);
			temp = list;
			check_variable_copy2(temp, dollar, new_text);
		}
		if (ast->token->value[i])
			new_text[dollar->k++] = ast->token->value[i++];
	}
	new_text[dollar->k] = '\0';
	free(dollar->variable);
	free(dollar);
	if (ft_strcmp(new_text, "") != 0)
	{
		free(ast->token->value);
		ast->token->value = new_text;
	}
	else
		free(new_text);
}

void	dollar_exit_status(t_ast *ast, t_minishell *minishell)
{
	t_dollar	*dollar;
	int			i;
	char		*new_text;

	i = 0;
	dollar = malloc(sizeof(t_dollar));
	dollar->j = 0;
	dollar->k = 0;
	new_text = malloc(sizeof(char) * 2048);
	while (ast->token->value[i])
	{
		if (ast->token->value[i] == '$')
		{
			dollar->variable = get_variable(ast->token->value, &i);
			check_variable_copy(dollar, new_text, minishell, &i);
		}
		if (ast->token->value[i])
			new_text[dollar->j++] = ast->token->value[i++];
	}
	new_text[dollar->j] = '\0';
	free(dollar->variable);
	free(dollar);
	if (ft_strcmp(new_text, "") != 0)
	{
		free(ast->token->value);
		ast->token->value = new_text;
	}
	else
		free(new_text);
}

char	*get_variable_env(char	*text)
{
	char	*variable;
	int		i;

	variable = NULL;
	i = 0;
	while (text[i] != '=')
		i++;
	variable = ft_substr(text, 0, i);
	return (variable);
}

void	check_variable_env(char **env, t_dollar *dollar, char *new_text)
{
	int	i;
	char *env_var;

	dollar->j = 0;
	i = 0;
	while (env[i])
	{
		env_var = get_variable_env(env[i]);
		if (ft_strcmp(dollar->variable, env_var) == 0)
		{
			while (env[i][dollar->j] != '=')
				dollar->j++;
			dollar->j++;
			while (env[i][dollar->j])
				new_text[dollar->k++] = env[i][dollar->j++];
			*(dollar->flag) = 1;
			dollar->j = 0;
			free(env_var);
			break ;
		}
		free(env_var);
		i++;
	}
}

void	ft_dollar_env(t_ast *ast, char **env, int *flag)
{
	t_dollar	*dollar;
	char		*new_text;
	char		*str;
	int				i;

	i = 0;
	str = ast->token->value;
	dollar = malloc(sizeof(t_dollar));
	new_text = malloc(sizeof(char) * 2048);
	dollar->flag = flag;
	dollar->k = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollar->variable = get_variable(str, &i);
			check_variable_env(env, dollar, new_text);
		}
		if (str[i])
			new_text[dollar->k++] = str[i++];
	}
	new_text[dollar->k] = '\0';
	flag = dollar->flag;
	free(dollar->variable);
	free(dollar);
	if (ft_strcmp(new_text, "") != 0)
	{
		free(ast->token->value);
		ast->token->value = new_text;
	}
	else
		free(new_text);
}

void	ft_dollar(t_ast *ast, t_assign *list, t_minishell *minishell)
{
	int	flag;

	flag = 0;
	if (ast == NULL)
		return ;
	if (ft_check_dollar(ast->token->value) && ft_strchr(ast->token->value, '?'))
		dollar_exit_status(ast, minishell);
	if (ft_check_dollar(ast->token->value) && ast->token->value[0] != '\'')
	{
		if (!list)
			ast->token->value = remove_dollar(ast);
		else if (list)
		{
			ft_dollar_env(ast, minishell->env, &flag);
			ft_dollar_list(ast, list, &flag);
			if (flag == 0)
				ast->token->value = remove_dollar(ast);
		}
	}
	ft_dollar(ast->left, list, minishell);
	ft_dollar(ast->right, list, minishell);
}
