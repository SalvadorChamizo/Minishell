/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sygnal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:49:21 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/11 11:46:25 by saroca-f         ###   ########.fr       */
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
			kill(command_sig, SIGINT);
			command_sig = 0;
		}
		else if (!command_sig)
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
	printf("Quit (core dumped)\n");
	kill (command_sig, SIGQUIT);
}

void	sigquit_signal(int flag)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	if (flag == 1)
		sa.sa_handler = quit_signal;
	else
		sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return ;
	}
}
