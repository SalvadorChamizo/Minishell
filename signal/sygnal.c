/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sygnal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:49:21 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/08 17:10:06 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

#ifndef ECHOCTL
#define ECHOCTL 0x00000040
#endif

void	signal_c(int signal_number)
{
	(void)signal_number;
	if (isatty(STDIN_FILENO))
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		printf("Quit (core dumped)");
	}
}

void	ft_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = signal_c;
	if(sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	printf("Signal SIGINT handled\n");
}
