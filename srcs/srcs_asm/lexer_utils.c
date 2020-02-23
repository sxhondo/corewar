/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 20:26:12 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 20:26:13 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					get_operator(char *name)
{
	int				i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(name, g_op_tab[i].name))
			return (g_op_tab[i].code);
		i++;
	}
	return (0);
}

int					is_label_char(char c)
{
	int				i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (LABEL_CHARS[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int					skip_void(t_cursor *p)
{
	while (p->f_data[p->pos] && (is_whitespace(p->f_data[p->pos])))
	{
		p->col += p->f_data[p->pos] == '\t' ? 4 : 1;
		p->pos += 1;
	}
	if (p->f_data[p->pos] == COMMENT_CHAR
		|| p->f_data[p->pos] == ALT_COMMENT_CHAR)
	{
		while (p->f_data[p->pos] && p->f_data[p->pos] != '\n')
		{
			p->pos += 1;
			p->col += 1;
		}
	}
	return (1);
}
