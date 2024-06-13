/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sygnal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:49:21 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/13 12:57:04 by saroca-f         ###   ########.fr       */
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
			g_command_sig = 0;
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
		g_command_sig = 0;
	}
}
