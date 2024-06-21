/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:46:39 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/21 11:17:45 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	access_format_error(va_list args, char c)
{
	int	cont;

	cont = 0;
	if (c == 'c')
		cont += print_char_error(va_arg(args, int));
	else if (c == 's')
		cont += print_str_error(va_arg(args, char *));
	else if (c == 'p')
		cont += print_ptr_error((unsigned long int)va_arg(args, void *));
	else if (c == 'd')
		cont += print_nbr_error(va_arg(args, int));
	else if (c == 'i')
		cont += print_nbr_error(va_arg(args, int));
	else if (c == 'u')
		cont += print_unsig_error(va_arg(args, unsigned int));
	else if (c == 'x')
		cont += print_hex_error(va_arg(args, unsigned int));
	else if (c == 'X')
		cont += print_hexup_error(va_arg(args, unsigned int));
	else if (c == '%')
		cont += print_char_error('%');
	return (cont);
}

int	check_format_error(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	ft_printf_err(const char *str, ...)
{
	va_list	args;
	int		i;
	int		cont;

	va_start(args, str);
	if (write(2, "", 0) == -1)
		return (-1);
	i = 0;
	cont = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && check_format_error(str[i + 1]))
		{
			cont += access_format_error(args, str[i + 1]);
			i++;
		}
		else
			cont += print_char_error(str[i]);
		i++;
	}
	va_end(args);
	return (cont);
}

/*int main(void)
{
	int n;

	n = 42;
	printf("La mía devuelve: %d\n", ft_printf("Imprime %c\n", 'h'));
	printf("La original devuelve: %d\n", printf("Imprime %c\n", 'h'));
	printf("La mía devuelve: %d\n", ft_printf("Imprime %d\n", 125));
	printf("La original devuelve: %d\n", printf("Imprime %d\n", 125));
	printf("La mía devuelve: %d\n", ft_printf("Imprime %p\n", &n));
	printf("La original devuelve: %d\n", printf("Imprime %p\n", &n));
	printf("La mía devuelve: %d\n", ft_printf("Imprime %s\n", "Hola mundo"));
	printf("La original devuelve: %d\n", printf("Imprime %s\n", "Hola mundo"));
}*/
