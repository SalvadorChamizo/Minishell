/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:21:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/12 17:49:57 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "structs.h"

//init
int			input_init(t_input *input, t_minishell *minishell);
t_minishell	*minishell_init(char **env);

//space control
int			ft_isspace(char c);
int			ft_skip_quote(t_input *input, char *text, t_token *new_token);
int			is_operator(char c);
t_tokentype	ft_operator(char *text);

//sygnal
void		sigint_signal(int signal_number);
void		sigquit_signal(int flag);

//others
void		ft_enter(void);
void		ft_close(void);

//memory
void		free_ast(t_ast **ast);
void		*free_split(char **str);
void		ft_list_clear(t_assign **list);

#endif