/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sygnal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:49:21 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/10 10:57:50 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

#ifndef ECHOCTL
#define ECHOCTL 0x00000040
#endif

struct termios	get_intterm(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term.c_lflag |= (ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
	return (term);
}

struct termios	get_quitterm(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
	return (term);
}

/*
int i = 0;  // Inicialización de la variable de control
while (i < columns - 1) {
    tputs(nd, 1, putchar);
    i++;  // Incremento de la variable de control
}*/

/*void move_cursor_to_end_of_line(void)
{
    int num_cols = tgetnum("co");  // obtener el número de columnas
    char *cm = tgetstr("cm", NULL);  // obtener la secuencia de escape para mover el cursor

    if (cm != NULL) 
	{
        cm = tgoto(cm, 0, num_cols - 1);  // mover el cursor a la última columna
        tputs(cm, 1, putchar);
    }
}*/


char	*cursor_pos(void)
{
	char *buf;
    unsigned int i;

	i = 0;
	buf = malloc(32);
	ft_bzero(buf, 32);
	write(STDOUT_FILENO, "\x1b[6n", 4);
	while (i < 31)
	{
		if (read(STDIN_FILENO, &buf[i], 1) != 1 || buf[i] == 'R')
			break;
		i++;
	}
	buf[i] = '\0';
	if (buf[0] != '\x1b' || buf[1] != '[')
		return ("");
	return (buf);
}

void	area_def(void)
{
	char	*move_cursor;
	char	area[2048];
	char	*ptr;
	int		columns;
	int 	rows;
	char 	*cursor_position;
	
	ptr = area;
	move_cursor = tgetstr("cm", &ptr);
	columns = tgetnum("co");
	rows = tgetnum("li");
	//cursor_position = tgoto(move_cursor, columns - 1, rows - 1);
	cursor_position = cursor_pos();
	tputs(cursor_position, 1, putchar);
}

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

void	ft_signal(void)
{
	//struct sigaction	sa;
	//struct termios		term;

	//sigemptyset(&sa.sa_mask);
	//term = get_term(SIGQUIT);
	//sa.sa_flags = 0;
	//sa.sa_handler = class_signal;
	signal(SIGINT, sigint_signal);
	signal(SIGQUIT, sigquit_signal);
	/*if(sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	if(sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}*/
}
