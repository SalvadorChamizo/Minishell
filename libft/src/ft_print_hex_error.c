/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:24:24 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/21 11:09:17 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	print_hex_error(unsigned int n)
{
	int	cont;

	cont = 0;
	if (n >= 16)
	{
		cont += print_hex_error(n / 16);
		cont += print_hex_error(n % 16);
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
			print_char_error((n - 10) + 'a');
			cont++;
		}
	}
	return (cont);
}
