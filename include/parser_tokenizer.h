/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenizer.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:15:34 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/25 11:32:25 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_TOKENIZER_H
# define PARSER_TOKENIZER_H

# include "structs.h"

//tokenizer

bool        is_identifier(char c);
void        identifer_case(t_input *input, t_token	*newtok, char *ret);
t_token     *ft_each_case(t_input *input, t_token *newtok, char *ret);
t_token     *get_next_token(t_input *input);

//tokenizer_operator

void        is_redir(t_input *input, t_token *newtok, char *ret);
void        ft_sop_def(t_input *input, t_token *nt, char *rt, t_tokentype t);
void        ft_dop_def(t_input *input, t_token *nt, char *rt, t_tokentype t);
bool        is_operator(char c);
void        ft_operator(t_input *input, t_token *newtok, char *ret);

//tokenizer_quote

int         is_quote(char c);
void        s_quote_case(t_input *input, t_token *nt, char *rt);
void        d_quote_case(t_input *input, t_token *nt, char *rt);

//tokenizer_utils

bool        is_assing(t_input *input, char *ret);
int         ft_isspace(char c);
int         ft_skip_spaces(t_input *input, char *text, t_token *new_token);
t_token     *ft_each_case(t_input *input, t_token *newtok, char *ret);

//parser
int			is_redirection_2(t_token *token);
int			ft_redirection(t_token *token, int state);
int			ft_word(t_token *token, int state);
int			ft_pipe(t_token *token, int state);
int			ft_parents(t_token *token, int state);
int			ft_parser_fda(t_minishell *minishell);
void		is_lva(t_input *input, t_token *token, char **env);

#endif
