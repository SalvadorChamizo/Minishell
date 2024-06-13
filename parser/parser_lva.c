/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lva.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:10:14 by saroca-f          #+#    #+#             */
/*   Updated: 2024/06/12 17:14:04 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	is_lva(t_input *input, t_token *token, char **env)
{
	int		ret;
	char	*str;

	ret = input->pos;
	str = NULL;
	while (ft_isspace(input->line[ret]))
		ret++;
	if (token->value && input->line[ret] == '\0')
	{
		ret = 0;
		while (env[ret])
		{
			if (!ft_strncmp(env[ret], "_=", 2))
				break ;
			ret++;
		}
		if (!env[ret] || !ft_strncmp(token->value, "$_", 2))
			return ;
		free(env[ret]);
		str = ft_strjoin("_=", token->value);
		env[ret] = ft_strdup(str);
		free(str);
	}
}
