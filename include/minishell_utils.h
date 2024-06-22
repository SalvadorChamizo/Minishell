/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:21:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/22 15:29:34 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "structs.h"

//init
int			input_init(t_input *input, t_minishell *minishell);
t_minishell	*minishell_init(char **env);
void    	init_variables(t_input *input, t_minishell *minishell);

//space control
int			ft_isspace(char c);
int			ft_skip_quote(t_input *input, char *text, t_token *new_token);
int			is_operator(char c);
t_tokentype	ft_operator(char *text);

//sygnal
void	    quit_signal(int signal_number);
void		sigint_signal(int signal_number);
void	    ft_heredoc_sigint_handler(int signal_number);

//others
void		ft_enter(void);
void		ft_close(void);

//memory
void		free_ast(t_ast **ast);
void		*free_split(char **str);
void		ft_list_clear(t_assign **list);

#endif