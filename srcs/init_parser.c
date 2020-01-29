/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:59:25 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/27 15:59:26 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

void 			add_operation(t_op **ops, t_op *elem)
{
	t_op 		*tmp;

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

t_parser         *init_parser(char *path)
{
    t_parser     *p;

    if ((p = ft_memalloc(sizeof(t_parser))) == NULL)
        display_error(CANT_ALLOCATE);
    if ((p->fd = open(path, O_RDONLY)) < 0)
        display_error(CANT_OPEN);
	p->ops = NULL;
	p->pos = 0;
    return (p);
}

t_op 			*init_operation()
{
	t_op 		*elem;

	if ((elem = ft_memalloc(sizeof(t_op))) == NULL)
		display_error(CANT_ALLOCATE);
	return (elem);
}