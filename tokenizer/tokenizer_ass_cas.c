/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_ass_cas.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:12:25 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/10 13:20:25 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

int	assdetection(t_input *minishell, char *ret)
{
	int	j;

	j=minishell->pos;
	while (!isspace(ret[j]) && ret[j] != '\0')
	{
		j++;
	}
	return (0);
}