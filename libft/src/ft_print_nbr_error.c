/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:02:07 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/21 11:11:14 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	print_nbr_error(int n)
{
	int		cont;
	char	c;

	cont = 0;
	if (n == -2147483648)
	{
		write(2, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		n = -n;
		write(2, "-", 1);
		cont++;
	}
	if (n >= 10)
		cont += print_nbr_error(n / 10);
	c = '0' + n % 10;
	write(2, &c, 1);
	cont++;
	return (cont);
}
