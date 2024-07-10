/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_underscore_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:28:33 by saroca-f          #+#    #+#             */
/*   Updated: 2024/07/10 14:31:39 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	underscore_init(int *i, int *j, int *flag)
{
	*i = 0;
	*j = 0;
	*flag = 0;
}

int	simple_quote_control(int flag)
{
	if (flag == 0)
		flag = 1;
	else if (flag == 1)
		flag = 0;
	return (flag);
}

int	double_quote_control(int flag)
{
	if (flag == 0)
		flag = 2;
	else if (flag == 2)
		flag = 0;
	return (flag);
}
