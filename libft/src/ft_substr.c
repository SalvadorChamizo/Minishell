/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:21:50 by schamizo          #+#    #+#             */
/*   Updated: 2024/04/29 19:39:34 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	char	*p;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	s1 = malloc(len + 1);
	if (s1 == NULL)
		return (NULL);
	p = s1;
	while (len--)
	{
		*p = s[start];
		p++;
		start++;
	}
	*p = '\0';
	return (s1);
}

/* Aloja memoria para un substring y copia de un string dado*/