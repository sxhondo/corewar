/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:18:17 by sxhondo           #+#    #+#             */
/*   Updated: 2019/05/04 13:50:41 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!content || !content_size)
	{
		tmp->content = NULL;
		tmp->next = 0;
	}
	else
	{
		if (!(tmp->content = ft_memalloc(content_size)))
		{
			free(tmp);
			return (NULL);
		}
		ft_memmove(tmp->content, content, content_size);
		tmp->content_size = content_size;
	}
	tmp->next = NULL;
	return (tmp);
}
