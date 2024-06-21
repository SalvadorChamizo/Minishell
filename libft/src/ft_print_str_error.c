/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:06:07 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/21 11:06:51 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	print_str_error(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		str = "(null)";
	while (str[len] != '\0')
		len++;
	write(2, str, len);
	return (len);
}
