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

#include "d_asm.h"

t_parser         *init_parser(char *path)
{
    t_parser     *p;

    if ((p = ft_memalloc(sizeof(t_parser))) == NULL)
        display_error(CANT_ALLOCATE);
    if ((p->fd = open(path, O_RDONLY)) < 0)
        display_error(CANT_OPEN);
    // p->lc_total = 0u;
    return (p);
}