/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:59:20 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/12 11:58:02 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>
# include <termios.h>

//TOKENIZER

typedef enum e_tokentype
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_ASSING,
	T_EOF,
}	t_tokentype;

typedef struct s_token
{
	char		*value;
	t_tokentype	type;
	bool		space;
}	t_token;

typedef struct s_input
{
	t_token	*current_token;
	char	*line;
	char	**path;
	int		pos;
	int		error;
}	t_input;

typedef struct s_syntax
{
	t_token			*token;
	struct s_syntax	*left;
	struct s_syntax	*right;
}	t_syntax;

//PARSER

typedef enum e_nodetype
{
	N_IDENTIFIER,
	N_COMMAND,
	N_ARGUMENT,
	N_BUILTIN,
	N_REDIRECTION,
	N_FILE,
	N_HEREDOC,
	N_DELIMITER,
	N_PIPELINE,
	N_ASSIGN,
	N_DIRECTORY,
}	t_nodetype;

typedef struct s_assign_list
{
	char					*variable;
	char					*value;
	struct s_assign_list	*next;
}	t_assign;

typedef struct s_ast
{
	t_nodetype		type;
	t_token			*token;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_idenlst
{
	t_token				*token;
	struct s_idenlst	*next;
	struct s_idenlst	*prev;
}	t_idenlst;

typedef struct s_minishell
{
	t_input			*input;
	t_ast			*ast;
	t_assign		*list;
	struct termios	termios;
	char			**env;
	int				line_number;
	int				status;
	int				stdin_fd;
	int				stdout_fd;
	int				pipe_in[2];
	int				pipe_out[2];
	int				pipe_aux[2];
	int				pipe_check;
}	t_minishell;

//EXPANSER

typedef struct s_dollar
{
	char	*variable;
	char	*new_text;
	int		j;
	int		k;
	int		*flag;
}	t_dollar;

#endif