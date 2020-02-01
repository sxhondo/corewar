/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:38:51 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/01 18:38:51 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

t_part	*create_part(char *str, size_t size)
{
	t_part	*new;

	if ((new = (t_part *)ft_memalloc(sizeof(t_part))))
	{
		new->content = str;
		new->size = size;
		new->next = NULL;
	}
	return (new);
}

void	add_part(t_part **list, t_part *new)
{
	t_part	*current;

	current = *list;
	if (current)
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else
		*list = new;
}

char	*parts_to_str(t_part *list, int len)
{
	char	*str;
	t_part	*current;
	int		size;

	size = 0;
	if (!(str = ft_strnew((size_t)len)))
		exit(1);
	current = list;
	while (current)
	{
		ft_memcpy(str, current->content, current->size);
		str += current->size;
		size += current->size;
		current = current->next;
	}
	return (str - len);
}

void	parts_free(t_part **list)
{
	t_part	*delete;
	t_part	*current;

	current = (*list);
	while (current)
	{
		delete = current;
		current = current->next;
		free(delete->content);
		free(delete);
	}
	(*list) = NULL;
}
