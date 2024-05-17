/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:56:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/17 12:18:32 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bash.h"

/*void	print_ast_helper(t_syntax *node, int depth, char *side)
{
	if (node == NULL)
		return ;
	if (node->token->type == T_IDENTIFIER)
	{
		printf(RED"%*s%s"RESET""BLUE"%d "YELLOW"IDENTIFIER:"RESET" %s\n", depth * 2, "", side, node->token->type, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->token->type == T_LESS || node->token->type == T_GREAT || node->token->type == T_DGREAT)
	{
		printf(RED"%*s%s"RESET""BLUE"%d "YELLOW"REDIRECTION:"RESET" %s\n", depth * 2, "", side, node->token->type, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->token->type == T_COMMAND)
	{
		printf(RED"%*s%s"RESET""BLUE"%d "YELLOW"COMMAND:"RESET" %s\n", depth * 2, "", side, node->token->type, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->token->type == T_ASS)
	{
		printf(RED"%*s%s"RESET""BLUE"%d "YELLOW"ASSIGNMENT:"RESET" %s\n", depth * 2, "", side, node->token->type, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->token->type == T_BUILTIN)
	{
		printf(RED"%*s%s"RESET""BLUE"%d "YELLOW"BUILTIN:"RESET" %s\n", depth * 2, "", side, node->token->type, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if(node->token->type == T_ARGUMENT)
	{
		printf(RED"%*s%s"RESET""YELLOW"ARGUMENT:"RESET" %s\n", depth * 2, "", side, node->token->type, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->token->type == T_DELIMITER)
	{
		printf(RED"%*s%s"RESET""BLUE"%d "YELLOW"LIMITER:"RESET" %s\n", depth * 2, "", side, node->token->type, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->token->type == T_FILE)
	{
		printf(RED"%*s%s"RESET""BLUE"%d "YELLOW"FILE:"RESET" %s\n", depth * 2, "", side, node->token->type, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else if (node->token->type == T_DLESS)
	{
		printf(RED"%*s%s"RESET""BLUE"%d "YELLOW"HEREDOC:"RESET" %s\n", depth * 2, "", side, node->token->type, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else
	{
		printf(RED"%*s%s"RESET""BLUE"%d "YELLOW"PIPELINE:"RESET" %s\n", depth * 2, "", side, node->token->type, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
}

void	print_ast(t_ast *root)
{
	printf(YELLOW"Arbol desplegado:\n"RESET);
	print_ast_helper(root, 0, "root: ");
}*/

/* void	print_assignment(t_assign_list *list)
{
	t_assign_list	*temp;
	int				i;

	i = 1;
	temp = list;
	if (!list)
		printf(BLUE"No assignments\n"RESET);
	else
	{
		printf(BLUE"\nAssignment List\n"RESET);
		while (temp)
		{
			printf("Node %d: Variable = %s, Value = %s\n", i, temp->variable, temp->value);
			temp = temp->next;
			i++;
		}		
	}
} */

////////////////////////////////////////////////////////////////////////////////

/* void	print_ast_helper(t_syntax *node, int depth, char *side) node->token->type,
{
	if (node == NULL)
		return ;
	if(node->token->type == NUM)
		printf(GREEN"%*s%sNUM:"RESET" %u\n", depth * 2, "", side, node->token->type, node->token->type);
	else if(node->token->type == UNIOP)
	{
		printf("%*s%sUNIOP: %s\n", depth * 2, "", side, node->token->type, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else
	{
		printf(YELLOW"%*s%s"MAGENTA"%s "GREEN"->"RESET" %u\n", depth * 2, "", side, node->token->type, node->token->value, node->token->type);
		print_ast_helper(node->left, depth + 2, "left: ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
}

void	print_ast(t_syntax *root)
{
	print_ast_helper(root, 0, "root: ");
} */

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
	//t_ast				*syntax;
	t_token				*current_token;
	int 				i;

	i = 0;
	(void)argc;
	(void)argv;
	//ft_enter(); eslogan de entrada
	while (1)
	{
		input = malloc(sizeof(t_input));
		input_init(input, env);
		add_history(input->line);
		if (!ft_strncmp(input->line, "exit", 4))
		{
			//ft_exit(); eslogan de salida
			break ;
		}
		else
		{
			current_token = get_next_token(input);
			printf("ENTRA\n");
			while (current_token->type != T_EOF)
			{
				free(current_token);
				current_token = get_next_token(input);
				i++;
			}
			free(current_token);
			input->pos = 0;
			//syntax = ft_expr(input);
			//ft_expanser(syntax);
			//print_ast(syntax);
			free(input->line);
		}
		free(input);
	}
	return (0);
}
