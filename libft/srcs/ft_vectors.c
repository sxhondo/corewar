/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:34:12 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/03 18:39:48 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_vec_del(t_vec **vec)
{
	free((*vec)->data);
	free(*vec);
	*vec = NULL;
}

t_vec		*ft_vec_resize(t_vec **vec)
{
	void	*data;

	data = (*vec)->data;
	if (!((*vec)->data = ft_memalloc((*vec)->total * (*vec)->type)))
		return (NULL);
	(*vec)->data = ft_memcpy((*vec)->data, data, (*vec)->total * (*vec)->type);
	(*vec)->capacity = (*vec)->total;
	free(data);
	return (*vec);
}

t_vec		*ft_vec_add(t_vec **vec, void *item)
{
	void	*tmp;
	t_vec	*p;

	if (!*vec)
		return (NULL);
	p = *vec;
	tmp = p->data;
	if (p->total >= p->capacity)
	{
		if (!(p->data = ft_memalloc(p->capacity * p->type * 2)))
		{
			ft_memdel(&(p->data));
			ft_memdel((void*)&p);
			return (NULL);
		}
		ft_memcpy(p->data, tmp, p->capacity * p->type);
		ft_memdel(&tmp);
		p->capacity *= 2;
	}
	ft_memcpy(p->data + (p->type * p->total), item, p->type);
	p->total++;
	return (p);
}

t_vec		*ft_vec_init(size_t size, int type)
{
	t_vec	*vec;

	if (!size || !(vec = (t_vec*)malloc(sizeof(t_vec))))
		return (NULL);
	vec->capacity = size;
	vec->total = 0;
	vec->type = type;
	if (!(vec->data = ft_memalloc(size * type)))
	{
		free(vec);
		return (NULL);
	}
	return (vec);
}
