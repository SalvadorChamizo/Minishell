/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenizer.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:15:34 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/10 12:39:56 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_TOKENIZER_H
# define PARSER_TOKENIZER_H

# include "structs.h"

//tokenizer

bool		is_identifier(char c);
void		identifer_case(t_input *input, t_token	*newtok, char *ret);
t_token		*ft_each_case(t_input *input, t_token *newtok, char *ret);
t_token		*get_next_token(t_input *input);

//tokenizer_operator

void		is_redir(t_input *input, t_token *newtok, char *ret);
void		ft_sop_def(t_input *input, t_token *nt, char *rt, t_tokentype t);
void		ft_dop_def(t_input *input, t_token *nt, char *rt, t_tokentype t);
bool		is_operator(char c);
void		ft_operator(t_input *input, t_token *newtok, char *ret);

//tokenizer_quote

int			is_quote(char c);
void		s_quote_case(t_input *input, t_token *nt, char *rt);
void		d_quote_case(t_input *input, t_token *nt, char *rt);

//tokenizer_utils

bool		is_assing(t_input *input, char *ret);
int			ft_isspace(char c);
int			ft_skip_spaces(t_input *input, char *text, t_token *new_token);
t_token		*ft_each_case(t_input *input, t_token *newtok, char *ret);

//parser_fda

int			check_identifier(t_token *token);
int			parser_fda_aux(t_token **token, int state);
int			finish_fda(t_token **token, int state, int level);
int			ft_parser_fda(t_minishell *minishell);

//parser_fda_utils

int			is_redirection_2(t_token *token);
int			ft_redirection(t_token *token, int state);
int			ft_word(t_token *token, int state);
int			ft_pipe_status(t_token *token, int state);
int			ft_parents(t_token *token, int state);

//parser_fda_error

int			check_syntax(t_token *token, int state);
void		print_error_syntax(int level, int state);
void		syntax_problem(t_token *token, int level, int state);

//parser_ast

t_ast		*ft_assignment(t_input *input, t_idenlst **list);
t_ast		*ft_identifier(t_input *input, t_idenlst **list);
t_ast		*ft_infile(t_input *input, t_idenlst **list);
t_ast		*ft_outfile(t_input *input, t_idenlst **list);
t_ast		*ft_parser_ast(t_input *input);

//parser_ast_utils

void		ft_eat(t_input *input, t_tokentype type);
void		ft_eat_aux(t_input *input);
int			is_redirection(t_token *token);
t_ast		*ft_parser_aux(t_ast *ast, t_ast *ast2, t_idenlst **list);

//parser_ast_list

void		ft_add_identifier_front(t_idenlst **lst, t_idenlst *new);
void		ft_lstadd_identifier(t_idenlst **lst, t_idenlst *new);
t_idenlst	*ft_lstnew_identifier(t_token *token);

//parser_ast_nodes

t_nodetype	return_type(t_token *token);
t_ast		*new_i_node(t_token *token);
t_ast		*iden_node(t_idenlst *lst);
t_ast		*bi_node(t_ast *left, t_token *op, t_ast *right);

//parser_undersocre

void	ft_underscore(t_minishell *minishell, t_token *token);
int	    simple_quote_control(int flag);
int	    double_quote_control(int flag);

#endif
