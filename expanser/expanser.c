/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:11:31 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/31 15:04:17 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	check_builtin(char *text)
{
	if (!ft_strcmp(text, "echo"))
		return (1);
	else if (!ft_strcmp(text, "cd"))
		return (1);
	else if (!ft_strcmp(text, "pwd"))
		return (1);
	else if (!ft_strcmp(text, "export"))
		return (1);
	else if (!ft_strcmp(text, "unset"))
		return (1);
	else if (!ft_strcmp(text, "env"))
		return (1);
	else if (!ft_strcmp(text, "exit"))
		return (1);
	return (0);
}

void	expand_builtin(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->type == N_IDENTIFIER && check_builtin(ast->token->value))
		ast->type = N_BUILTIN;
	expand_builtin(ast->left);
	expand_builtin(ast->right);
}

void	expand_command2(t_ast *ast)
{
	char	*str;
	if (ast == NULL)
		return ;
	if (ast->type == N_COMMAND)
	{
		str = ft_strjoin("/", ast->token->value);
		free(ast->token->value);
		ast->token->value = str;
	}
	expand_command2(ast->left);
	expand_command2(ast->right);
}

int	check_prev(t_ast *prev)
{
	if (prev->type != N_IDENTIFIER && prev->type != N_COMMAND
		&& prev->type != N_ARGUMENT)
		return (1);
	return (0);
}

int	check_prev2(t_ast *prev)
{
	if (prev->type == N_IDENTIFIER || prev->type == N_COMMAND
		|| prev->type == N_ARGUMENT)
		return (1);
	return (0);
}

void	expand_command(t_ast *ast, t_ast *prev, int flag)
{
	if (ast == NULL)
		return ;
	if (ast->type == N_IDENTIFIER && flag == 0
		&& !check_builtin(ast->token->value))
		ast->type = N_COMMAND;
	if (prev != NULL)
	{
		if (ast->type != N_REDIRECTION && ast->type != N_HEREDOC
			&& ast->type != N_PIPELINE)
		{
			if (check_prev(prev) && ast->type != N_ASSIGN
				&& flag == 1 && !check_builtin(ast->token->value))
				ast->type = N_COMMAND;
			else if (check_prev2(prev) && !check_builtin(ast->token->value) && ast->type != N_ASSIGN)
				ast->type = N_ARGUMENT;
		}
	}
	if (ast->type != N_REDIRECTION && ast->type != N_HEREDOC)
		expand_command(ast->left, ast, 1);
	else
		expand_command(ast->left, ast, 0);
	expand_command(ast->right, ast, 1);
}

void	expand_command_3(t_ast *ast, char **path)
{
	int		i;
	char	*str;

	i = 0;
	if (!ast)
		return ;
	if (ast->type == N_COMMAND)
	{
		while (path[i] != NULL)
		{
			str = ft_strjoin(path[i], ast->token->value);
			if (access(str, F_OK | X_OK) == 0)
			{
				free(ast->token->value);
				ast->token->value = str;
				break ;
			}	
			free(str);
			str = NULL;
			i++;
		}
	}
	expand_command_3(ast->left, path);
	expand_command_3(ast->right, path);
}

void	expand_redir(t_ast *ast, t_ast *prev, int flag)
{
	if (ast == NULL)
		return ;
	if (prev != NULL)
	{
		if (prev->type == N_REDIRECTION && flag == 1
			&& (ast->type != N_REDIRECTION && ast->type != N_HEREDOC))
			ast->type = N_FILE;
		else if (prev->type == N_HEREDOC && flag == 1
			&& (ast->type != N_REDIRECTION && ast->type != N_HEREDOC))
			ast->type = N_DELIMITER;
	}
	expand_redir(ast->left, ast, 1);
	expand_redir(ast->right, ast, 0);
	return ;
}

int	check_equal(char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i] == '=' && i != 0)
			return (1);
		i++;
	}
	return (0);
}

void	expand_assignment(t_ast *ast, t_ast *prev)
{
	if (ast == NULL)
		return ;
	if (prev == NULL && check_equal(ast->token->value))
		ast->type = N_ASSIGN;
	if (prev != NULL)
	{
		if (prev->type != N_COMMAND && prev->type != N_IDENTIFIER
			&& prev->type != N_ARGUMENT && check_equal(ast->token->value))
			ast->type = N_ASSIGN;
	}
	expand_assignment(ast->left, ast);
	expand_assignment(ast->right, ast);
}

t_assign_list	*new_assignment(char *text, t_assign_list *list)
{
	t_assign_list	*new_node;
	t_assign_list	*temp;
	char			*word;
	int				i;

	i = 0;
	while (text[i] != '=')
		i++;
	word = ft_substr(text, 0, i);
	if (list)
	{
		temp = list;
		while (temp)
		{
			if (!ft_strcmp(word, temp->variable))
			{
				temp->value = ft_substr(text, i + 1, ft_strlen(text) - i);
				return (NULL);
			}
			temp = temp->next;
		}
	}
	new_node = malloc(sizeof(t_assign_list));
	new_node->variable = word;
	new_node->value = ft_substr(text, i + 1, ft_strlen(text) - i);
	new_node->next = NULL;
	return (new_node);
}

void	ft_assign_add_back(t_assign_list **lst, t_assign_list *new)
{
	t_assign_list	*last;

	last = *lst;
	if (!last)
		*lst = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	store_assignment(t_ast *ast, t_assign_list **list)
{
	t_assign_list	*new_node;

	new_node = NULL;
	if (ast == NULL || ast->token->type == T_PIPE
		|| ast->token->type == T_IDENTIFIER)
		return ;
	if (ast->type == N_ASSIGN)
	{
		new_node = new_assignment(ast->token->value, *list);
		ft_assign_add_back(list, new_node);
	}
	store_assignment(ast->left, list);
	store_assignment(ast->right, list);
}

void	expand_quotes(t_ast *ast)
{
	char	*str;
	if (ast == NULL)
		return ;
	while (ast->token->value[0] == '\"' || ast->token->value[0] == '\'')
	{
		if (ast->token->value[0] == '\"')
		{
			str = ft_strtrim(ast->token->value, "\"");
			free(ast->token->value);
			ast->token->value = str;
		}
		if (ast->token->value[0] == '\'')
		{
			str = ft_strtrim(ast->token->value, "\'");
			free(ast->token->value);
			ast->token->value = str;
		}
	}
	expand_quotes(ast->left);
	expand_quotes(ast->right);
}

void	ft_store_env(t_assign_list **list, char **envp)
{
	t_assign_list	*new_node;
	int	i;

	new_node = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = new_assignment(envp[i], *list);
		ft_assign_add_back(list, new_node);
		i++;
	}
}

char	**ft_get_path(char **envp)
{
	int	i;
	char	*str;
	char	**split;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	str = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	split = ft_split(str, ':');
	free(str);
	return (split);
}

void	ft_expanser(t_ast *ast, t_minishell *minishell, char **envp)
{
	t_ast	*ast_temp;
	char	**path;
	int		i;

	i = 0;
	path = ft_get_path(envp);
	ast_temp = ast;
	expand_redir(ast, NULL, 0);
	ft_dollar(ast, minishell->list);
	expand_quotes(ast);
	expand_assignment(ast, NULL);
	expand_command(ast, NULL, 0);
	expand_builtin(ast);
	expand_command2(ast);
	expand_command_3(ast, path);
	store_assignment(ast, &minishell->list);
	free_split(path);
	print_assignment(minishell->list);
}
