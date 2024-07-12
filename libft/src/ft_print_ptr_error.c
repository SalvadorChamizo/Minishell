/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:18:16 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/21 11:12:57 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	print_ptr_error(unsigned long int n)
{
	int	cont;

	cont = 0;
	cont += print_str_error("0x");
	cont += print_ptrhex_error(n);
	return (cont);
}
