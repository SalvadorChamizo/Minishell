/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sygnal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:49:21 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/10 11:45:37 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	sigint_signal(int signal_number)
{
	if (signal_number == SIGINT)
	{
		if (command_sig)
		{
			printf("\n");
			kill(command_sig, SIGKILL);
			command_sig = 0;
		}
		else if(!command_sig)
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	sigquit_signal(int signal_number)
{
	if (signal_number == SIGQUIT)
	{
		if (command_sig)
		{
			printf("Quit (core dumped)\n");
			kill (command_sig, SIGKILL);
			command_sig = 0;
		}
	}
}
