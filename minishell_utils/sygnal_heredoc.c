/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sygnal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:56:25 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/09 20:03:19 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	int_signal_heredoc(int signal_number)
{
	(void)signal_number;
	write(1, "\n", 1);
	exit(130);
}

void	heredoc_signal(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = int_signal_heredoc;
	sa_int.sa_flags = 0;
	/* memset(&sa_int, 0, sizeof(sa_int));
    sa_int.sa_handler = int_signal_heredoc;
    sigfillset(&sa_int.sa_mask); */
	if (sigaction(SIGINT, &sa_int, NULL) < 0)
	{
		perror("sigaction");
		return ;
	}
}
