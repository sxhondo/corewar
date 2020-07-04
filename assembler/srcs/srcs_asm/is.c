/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skipers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 20:20:28 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 20:20:28 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					skip_nl(t_cursor *p)
{
	while (p->lex && p->lex->type == NL)
		p->lex = p->lex->next;
	return (1);
}

int					is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v');
}

int					is_num(char c)
{
	return (ft_isdigit(c) || c == '-');
}

int					is_liri_attr(char c)
{
	return (c == LABEL_CHAR || is_label_char(c) || is_num(c));
}
