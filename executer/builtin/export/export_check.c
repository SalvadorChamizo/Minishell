/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:14:42 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/14 16:31:47 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bash.h"

bool	identifier_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (false);
	}
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && (str[i] != '+' && str[i + 1] != '=')
			&& str[i] != '_')
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (false);
		}
		i++;
	}
	return (true);
}
