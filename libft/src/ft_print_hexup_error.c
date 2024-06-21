/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexup_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:25:10 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/21 11:10:13 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	print_hexup_error(unsigned int n)
{
	int	cont;

	cont = 0;
	if (n >= 16)
	{
		cont += print_hexup_error(n / 16);
		cont += print_hexup_error(n % 16);
	}
	else
	{
		if (n < 10)
		{
			print_char_error('0' + n);
			cont++;
		}
		else if (n >= 10)
		{
			print_char_error((n - 10) + 'A');
			cont++;
		}
	}
	return (cont);
}
