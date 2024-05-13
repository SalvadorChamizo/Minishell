/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:11:12 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/09 18:52:59 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_control(int status)
{
	if (status == 1 || status == 6 || status == 4)
		return (true);
	return (false);
}

bool	is_word(t_tokentype val)
{
	if (val == T_IDENTIFIER || val == T_DQUOTE || val == T_SQUOTE
		|| val == T_ASS)
		return (true);
	return (false);
}

bool	first_comp(t_tokentype val, t_parscontrol *control)
{
	if ((control->status == 1 || control->status == 6) && val == T_O_PARENT)
	{
		control->level++;
		return (true);
	}
	else if (ft_control(control->status) && (val == T_LESS || val == T_GREAT
			|| val == T_DGREAT || val == T_DLESS))
	{
		control->status = 3;
		return (true);
	}
	else if ((ft_control(control->status) || control->status == 3)
		&& (is_word(val)))
	{
		control->status = 4;
		return (true);
	}
	else if (control->status == 7 && is_word(val))
	{
		control->status = 5;
		return (true);
	}
	return (false);
}

bool	parser(t_tokentype val, t_parscontrol *control)
{
	if (first_comp(val, control))
		return (true);
	else if ((control->status == 4 || control->status == 5) && val == T_PIPE)
	{
		control->status = 6;
		return (true);
	}
	else if ((control->status == 5) && (val == T_LESS
			|| val == T_GREAT || val == T_DGREAT || val == T_DLESS))
	{
		control->status = 7;
		return (true);
	}
	else if ((control->status == 1 || control->status == 4 ||
			control->status == 6) && val == T_C_PARENT && control->level > 0)
	{
		control->level--;
		control->status = 5;
		return (true);
	}
	else
		return (false);
}
