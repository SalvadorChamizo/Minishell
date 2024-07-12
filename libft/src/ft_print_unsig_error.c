/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsig_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:47:12 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/21 11:14:40 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	print_unsig_error(unsigned int n)
{
	int		cont;
	char	c;

	cont = 0;
	if (n >= 10)
		cont += print_unsig_error(n / 10);
	c = '0' + n % 10;
	write(2, &c, 1);
	cont++;
	return (cont);
}
