/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sygnal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:56:25 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/10 09:33:03 by saroca-f         ###   ########.fr       */
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
	if (sigaction(SIGINT, &sa_int, NULL) < 0)
	{
		perror("sigaction");
		return ;
	}
}
