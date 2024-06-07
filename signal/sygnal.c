/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sygnal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:49:21 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/07 19:35:40 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

#ifndef ECHOCTL
#define ECHOCTL 0x00000040
#endif

int	disable_signal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1) 
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
    }
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
	{
         perror("tcsetattr");
	}
	return (0);
}

void	signal_c(int signal_number)
{
	char	*user;
	char	*computer;
	
	user = getenv("USER");
	computer = getenv("SESSION_MANAGER");
	computer = ft_substr(computer, 6, 6);
	if (isatty(STDIN_FILENO) && signal_number == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf(RED"%s@%s ^C\n"RESET, user, computer);
		write(1, RED"^C\n", 9);
		rl_redisplay();
		g_signal = 1;
	}
}

void	signal_slach(int signal_number)
{
	char	*user;
	char	*computer;
	
	user = getenv("USER");
	computer = getenv("SESSION_MANAGER");
	computer = ft_substr(computer, 6, 6);
	if (isatty(STDIN_FILENO) && signal_number == SIGQUIT)
	{
		rl_on_new_line();
		printf(RED"%s@%s"RESET, user, computer);
		rl_redisplay();
	}
	/*if (signal_number == SIGQUIT)
	{
		if (isatty(STDIN_FILENO))
			signal(SIGQUIT, SIG_IGN);
		else
		{
			printf("ENTRA SLACH "RED"NO"RESET" INTERACTIVO\n");
			signal(SIGQUIT, SIG_DFL);
			printf("Quit (core dumped)");
		}
	}*/
}
