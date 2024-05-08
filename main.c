/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:19:02 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/08 14:23:48 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast_helper(t_syntax *node, int depth, char *side)
{
	if (node == NULL)
		return ;
	if (node->type == NUM)
		printf(GREEN"%*s%sNUM:"RESET" %s\n", depth * 2, "", side, node->token->value);
	else if (node->type == UNIOP)
	{
		printf("%*s%sUNIOP: %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
	else
	{
		printf(YELLOW"%*s%sBINOP:"RESET" %s\n", depth * 2, "", side, node->token->value);
		print_ast_helper(node->left, depth + 2, "left:  ");
		print_ast_helper(node->right, depth + 2, "right: ");
	}
}

void	print_ast(t_syntax *root)
{
	print_ast_helper(root, 0, "root: ");
}

void	input_init(t_input *input, char **ev)
{
	int	i;

	i = 0;
	input->pos = 0;
	input->line = readline(RED"minishell> "RESET);
	//input->line = "First Second Third | Fourth";
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
	t_parscontrol		*control;
	t_syntax			*syntax;

	(void)argc;
	(void)argv;
	control = malloc(sizeof(t_parscontrol));
	control->level = 0;
	control->status = 1;
	ft_enter();
	while (1)
	{
		input = malloc(sizeof(t_input));
		input_init(input, env);
		add_history(input->line);
		if (!ft_strncmp(input->line, "exit", 4))
		{
			ft_exit();
			break ;
		}
		else
		{
			syntax = ft_pipe(input);
			ft_printf(RED"\n/////////////////////////////////////////\n\n"RESET);
			print_ast(syntax);
			free(input->line);
		}
		free(input);
	}
	return (0);
}
