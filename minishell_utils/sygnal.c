/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sygnal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:49:21 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/08 18:39:49 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	sigint_signal(int signal_number)
{
	if (signal_number == SIGINT)
	{
		if (g_command_sig)
		{
			printf("\n");
			kill(g_command_sig, SIGINT);
		}
		else if (!g_command_sig)
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	quit_signal(int signal_number)
{
	(void)signal_number;
	if (g_command_sig)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		kill(g_command_sig, SIGQUIT);
	}
}

/*void	int_signal_heredoc(int signal_number)
{
	(void)signal_number;
	exit(131);
}*/

void	ft_heredoc_sigint_handler(int signal_number)
{
	(void)signal_number;
	if (g_command_sig == 0)
	{
		write(1, "\n", 1);
		exit(SIGINT);
	}
}
