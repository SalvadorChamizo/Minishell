/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:10:18 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/28 16:12:53 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

char	*wish_ensambler(char const *s1, char const *s2)
{
	char	*s3;
	char	*p;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = malloc(len1 + len2 + 2);
	if (s3 == NULL)
		return (NULL);
	p = s3;
	while (len1--)
		*p++ = *s1++;
	*p++ = '/';
	while (len2--)
		*p++ = *s2++;
	*p = '\0';
	return (s3);
}

void	regret_basic(t_ast *tree)
{
	while (ft_strcmp(getcwd(NULL, 0), "/") != 0)
	{
		if (chdir("..") == -1)
		{
			cd_error(tree->left->token->value);
			break ;
		}
	}
}

