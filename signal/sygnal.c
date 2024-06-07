/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sygnal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:49:21 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/07 12:51:14 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	disable_signal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1) 
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
    }
	//term.c_lflag &= ~ECHOCTL;
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
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		printf(RED"%s@%s"RESET, user, computer);
		rl_redisplay();
		g_signal = 1;
	}
}

void	signal_slach(int signal_number)
{
	if (isatty(STDIN_FILENO) && signal_number == SIGQUIT)
	{
		rl_on_new_line();
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
