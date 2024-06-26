/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:53:00 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/26 17:45:36 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	*get_variable(char	*text, int *cur)
{
	char	*variable;
	int		start;

	variable = NULL;
	start = *cur + 1;
	if (text[*cur] == '$')
	{
		*cur = *cur + 1;
		while (text[*cur] != '\0' && ft_isalnum(text[*cur]))
			*cur = *cur + 1;
		variable = ft_substr(text, start, *cur - start);
	}
	return (variable);
}
