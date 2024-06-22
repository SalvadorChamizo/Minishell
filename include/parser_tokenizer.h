/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenizer.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:15:34 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/22 08:40:07 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_TOKENIZER_H
# define PARSER_TOKENIZER_H

# include "structs.h"

//tokenizer
t_token		*get_next_token(t_input *minishell);
int			ft_skip_spaces(t_input *input, char *text, t_token *new_token);
void		ft_sop_def(t_input *mshll, t_token *nt, char *rt, t_tokentype t);
void		ft_dop_def(t_input *mshll, t_token *nt, char *rt, t_tokentype t);
int			isquote(char c);
void		s_quote_case(t_input *mshll, t_token *nt, char *rt);
void		d_quote_case(t_input *mshll, t_token *nt, char *rt);
t_token		*tokenizer(t_input minishell);
bool		isoperator(char c);
bool        is_assing(t_input *minishell, char *ret);

//parser
int			is_redirection_2(t_token *token);
int			ft_redirection(t_token *token, int state);
int			ft_word(t_token *token, int state);
int			ft_pipe(t_token *token, int state);
int			ft_parents(t_token *token, int state);
int			ft_parser_fda(t_minishell *minishell);
void	    is_lva(t_input *input, t_token *token, char **env);

#endif
