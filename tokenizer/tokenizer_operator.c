/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:07:36 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/25 11:27:37 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	is_redir(t_input *input, t_token *newtok, char *ret)
{
	char	c;
	char	d;

	c = ret[input->pos];
	d = 0;
	if (ret[input->pos + 1])
		d = ret[input->pos + 1];
	if (c == '<' && d != '<')
		ft_sop_def(input, newtok, ret, T_LESS);
	else if (c == '>' && d != '>')
		ft_sop_def(input, newtok, ret, T_GREAT);
	else if (c == '<' && d == '<')
		ft_dop_def(input, newtok, ret, T_DLESS);
	else if (c == '>' && d == '>')
		ft_dop_def(input, newtok, ret, T_DGREAT);
}

void	ft_sop_def(t_input *input, t_token *nt, char *rt, t_tokentype t)
{
	nt->value = ft_substr(rt, input->pos, 1);
	if (!nt->value)
		return ;
	nt->type = t;
}

void	ft_dop_def(t_input *input, t_token *nt, char *rt, t_tokentype t)
{
	nt->value = ft_substr(rt, input->pos, 2);
	if (!nt->value)
		return ;
	nt->type = t;
	input->pos++;
}

bool	is_operator(char c)
{
	if (c == '\0')
		return (false);
	if (c == '<' || c == '>' || c == '|' || c == '(' || c == ')')
		return (true);
	return (false);
}

void	ft_operator(t_input *input, t_token *newtok, char *ret)
{
	char	c;

	c = ret[input->pos];
	if (c == '|')
		ft_sop_def(input, newtok, ret, T_PIPE);
	else if (c == '(')
		ft_sop_def(input, newtok, ret, T_O_PARENT);
	else if (c == ')')
		ft_sop_def(input, newtok, ret, T_C_PARENT);
	is_redir(input, newtok, ret);
	if (!newtok->value)
		return ;
	input->pos++;
}
