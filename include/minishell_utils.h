/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:21:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/26 17:24:43 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "structs.h"

//init
int			input_init(t_input *input, t_minishell *minishell);
t_minishell	*minishell_init(char **env);
void		init_variables(t_input *input, t_minishell *minishell);

//sygnal
void		quit_signal(int signal_number);
void		sigint_signal(int signal_number);
void		ft_heredoc_sigint_handler(int signal_number);

//others
void		ft_enter(void);
void		ft_close(void);

//memory
int 		free_ast(t_ast **ast, int num);
void		*free_split(char **str);
void		ft_list_clear(t_assign **list);

#endif