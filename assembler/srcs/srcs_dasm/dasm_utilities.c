/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:51:56 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/27 14:51:57 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

void			free_allocated(t_parser *p)
{
	t_op		*ptr;
	t_op		*next;

	ptr = p->ops;
	while (ptr)
	{
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
	ft_strdel(&p->comment);
	ft_strdel(&p->name);
	free(p);
}

void			d_error(int num)
{
	ft_fprintf(2, "error: ");
	ft_fprintf(2, "%s\n", g_errors[num]);
	exit(num);
}
