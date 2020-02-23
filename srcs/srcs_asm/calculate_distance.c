/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 20:01:09 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 20:01:10 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int32_t		check_empty_labels(t_lab *l, char *search, int32_t pos)
{
	while (l)
	{
		if (ft_strequ(l->name, search))
			return (pos);
		l = l->next;
	}
	return (-1);
}

static int32_t		search_label(t_ins *root, t_lab *un, char *search, int mod)
{
	t_lab			*l;
	t_ins			*r;
	int32_t			pos;

	pos = 0;
	r = root;
	while (r)
	{
		l = r->lab;
		while (l)
		{
			if (ft_strequ(l->name, search))
				return (mod == 0 ? -(pos + r->bytes) : pos);
			l = l->next;
		}
		pos += r->bytes;
		r = mod == 0 ? r->next : r->prev;
	}
	return (mod == 0 ? -1 : check_empty_labels(un, search, pos));
}

int32_t				calculate_distance(t_cursor *p, t_ins *curr, char *search)
{
	t_ins			*rev;
	int32_t			a;

	if ((a = search_label(curr->next, p->lab, search, 0)) == -1)
	{
		rev = curr;
		while (rev->next)
			rev = rev->next;
		while (rev && rev->row != curr->row)
			rev = rev->prev;
		a = search_label(rev, p->lab, search, 1);
	}
	return (a);
}
