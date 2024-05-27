/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:11:31 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/27 14:57:07 by schamizo         ###   ########.fr       */
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
	if (ast == NULL)
		return ;
	if (ast->type == N_COMMAND)
		ast->token->value = ft_strjoin("/", ast->token->value);
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
int	ft_check_dollar(char *text)
{
	int	i;

	i = 0;
	if (!text)
		return (0);
	while (text[i])
	{
		if (text[i] == '$' && text[i + 1] != ' '
			&& text[i + 1] != '\0' && text[i + 1] != '\"')
			return (1);
		i++;
	}
	return (0);
}

/*void ft_dollar(t_ast *ast, t_assign_list *list)
{
	char			*text;
	t_assign_list	*temp;
	int				flag;
	int				len;

	flag = 0;
	len = 0;
	if (ast == NULL)
		return ;
	if (ft_check_dollar(ast->token->value) && ast->token->value[0] != '\'')
	{
		if (!list)
			ast->token->value = ft_substr(ast->token->value, );
		else if (list)
		{
			temp = list;
			if (ast->token->type != N_COMMAND)
				text = ft_substr(ast->token->value, 1, ft_strlen(ast->token->value) - 1);
			else
				text = ft_substr(ast->token->value, 2, ft_strlen(ast->token->value) - 2);
			while (temp)
			{
				if (ft_strcmp(text, temp->variable) == 0)
				{
					ast->token->value = temp->value;
					flag = 1;
				}
				temp = temp->next;
			}
			if (flag == 0)
				ast->token->value = "";
		}
	}
	ft_dollar(ast->left, list);
	ft_dollar(ast->right, list);
}*/

char	*remove_dollar(t_ast *ast)
{
	char	*text;
	char	*new_text;
	int		i;
	int		j;

	text = ft_strdup(ast->token->value);
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
	return (new_text);
}

char	*get_variable(char	*text, int *cur)
{
	char	*variable;
	int		i;
	int		len;

	variable = NULL;
	len = 0;
	i = *cur + 1;
	if (text[*cur] == '$')
	{
		while(text[*cur] != ' ' && text[*cur] != '\0')
		{
			*cur = *cur + 1;
			len++;
		}
		printf("Falla en el malloc\n");
		variable = malloc(sizeof(char) * len);
		printf("O no\n");
		len = 0;
		while (text[i] != ' ' && text[i] != '\0' && text[i] != '\"')
		{
			printf("Falla en el bucle i = %d\n", i);
			variable[len] = text[i];
			len++;
			i++;
		}
	}
	return (variable);
}

void	ft_dollar_list(t_ast *ast, t_assign_list *list, int *flag)
{
	t_assign_list	*temp;
	char			*text;
	char			*variable;
	int				i;
	int				j;
	int				k;
	char			*new_text;


	temp = list;
	text = ast->token->value;
	i = 0;
	j = 0;
	k = 0;
	new_text = malloc(sizeof(char) * ft_strlen(text) * 2);
	while (text[i])
	{
		printf("Falla en i = %d\n", i);
		if (text[i] == '$')
		{
			printf("Antes de get_variable\n");
			variable = get_variable(text, &i);
			printf("Después de get_variable\n");
			printf("Variable es: %s\n", variable);
			while (temp)
			{
				if (ft_strcmp(variable, temp->variable) == 0)
				{
					while (temp->value[j])
					{
						printf("Llega a entrar aquí\n");
						new_text[k] = temp->value[j];
						j++;
						k++;
					}
					*flag = 1;
					j = 0;
					break ;
				}
				temp = temp->next;
			}
			temp = list;
		}
		new_text[k] = text[i];
		k++;
		i++;
	}
	ast->token->value = new_text;
}

void ft_dollar(t_ast *ast, t_assign_list *list)
{
	int				flag;
	int				len;

	flag = 0;
	len = 0;
	if (ast == NULL)
		return ;
	if (ft_check_dollar(ast->token->value) && ast->token->value[0] != '\'')
	{
		printf("Estamos dentro\n");
		if (!list)
			ast->token->value = remove_dollar(ast);
		else if (list)
		{
			ft_dollar_list(ast, list, &flag);
			printf("Valor de flag = %d\n", flag);
			if (flag == 0)
				ast->token->value = remove_dollar(ast);
		}
	}
	ft_dollar(ast->left, list);
	ft_dollar(ast->right, list);
}

void	expand_quotes(t_ast *ast)
{
	if (ast == NULL)
		return ;
	while (ast->token->value[0] == '\"' || ast->token->value[0] == '\'')
	{
		if (ast->token->value[0] == '\"')
		{
			ast->token->value = ft_strtrim(ast->token->value, "\"");
		}
		if (ast->token->value[0] == '\'')
		{
			ast->token->value = ft_strtrim(ast->token->value, "\'");
		}
	}
	expand_quotes(ast->left);
	expand_quotes(ast->right);
}

void	ft_expanser(t_ast *ast, t_minishell *minishell)
{
	t_ast			*ast_temp;
	t_assign_list	*list;

	list = NULL;
	ast_temp = ast;
	expand_redir(ast, NULL, 0);
	printf("Entramos\n");
	ft_dollar(ast, minishell->list);
	expand_quotes(ast);
	expand_assignment(ast, NULL);
	expand_command(ast, NULL, 0);
	expand_builtin(ast);
	expand_command2(ast);
	//print_ast(ast);
	store_assignment(ast, &minishell->list);
	print_assignment(minishell->list);
}
