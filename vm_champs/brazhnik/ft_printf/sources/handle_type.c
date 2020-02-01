/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 11:42:10 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/04 11:42:11 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

int		handle_type(t_placeholder *ph, va_list args, int *size, t_part **list)
{
	int		i;
	char	*str;
	t_part	*new;

	i = 0;
	while (i < (int)(sizeof(g_type) / sizeof(t_type)))
	{
		if (g_type[i].type == ph->type)
		{
			ph->padding = (ph->type == 'n') ? *size : 0;
			str = g_type[i].function(ph, args);
			if (ph->width == -1)
				return (-1);
			if (!(new = create_part(str, (size_t)ph->width)))
				exit(1);
			add_part(list, new);
			return (ph->width);
		}
		i++;
	}
	str = handle_inv_type(ph);
	if (!(new = create_part(str, (size_t)ph->width)))
		exit(1);
	add_part(list, new);
	return (ph->width);
}
