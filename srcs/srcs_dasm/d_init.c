/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:26:39 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 19:26:39 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

void				add_operation(t_op **ops, t_op *elem)
{
	t_op			*tmp;

	tmp = *ops;
	if (!*ops)
		*ops = elem;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
		elem->next = NULL;
	}
}

t_parser			*init_parser(char *path)
{
	t_parser		*p;

	if (!(p = ft_memalloc(sizeof(t_parser))))
		d_error(CANT_ALLOCATE);
	if ((p->fd = open(path, O_RDONLY)) < 0)
		d_error(CANT_OPEN);
	p->ops = NULL;
	p->pos = 0;
	return (p);
}

t_op				*init_operation(void)
{
	t_op			*elem;

	if ((elem = ft_memalloc(sizeof(t_op))) == NULL)
		d_error(CANT_ALLOCATE);
	return (elem);
}
