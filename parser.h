/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:18:16 by schamizo          #+#    #+#             */
/*   Updated: 2024/05/16 18:29:19 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "bash.h"

typedef enum e_nodetype
{
	N_COMMAND,
	N_ARGUMENT,
	N_REDIRECTION,
	N_OPERATOR,
	N_SQUOTE,
}	t_nodetype;

typedef enum e_tokentype
{
	T_IDENTIFIER,
	T_REDIRECTION,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_EOF,
}	t_tokentype;

typedef struct s_idenlst
{
	t_token				*token;
	struct s_idenlst	*next;
	struct s_idenlst	*prev;
}	t_idenlst;

typedef struct s_token
{
	char		*value;
	t_tokentype	type;
}	t_token;

typedef struct s_ast
{
	t_nodetype		*token;
	t_tokentype		type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_input
{
	char		*text;
	int			pos;
	t_idenlst	*list;
	t_token		*current_token;
}	t_input;

t_ast	*create_redirec_node(t_input *input, t_ast *root, t_token *token);
t_ast	*create_word_node(t_input *input, t_token *token, t_nodetype type, int check);
t_ast	*new_i_node(t_token *token);
t_ast	*new_b_node(t_ast *left, t_token *op, t_ast *right);
t_ast	*iden_node(t_idenlst *lst);
t_ast	*new_b_node2(t_ast *left, t_token *op, t_ast *right, t_ast *iden);

void	ft_eat_aux(t_input *input);

#endif