/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 17:17:46 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/01 17:17:46 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

static void	parse_str(char **ptr, int *size, t_part **list)
{
	char	*str;
	size_t	strlen;
	char	*percent;
	t_part	*new;

	percent = ft_strchr(*ptr, '%');
	strlen = (percent) ? (percent - *ptr) : ft_strlen(*ptr);
	if (strlen > 0)
	{
		if (!(str = ft_strnew(strlen)))
			exit(1);
		ft_strncpy(str, *ptr, strlen);
		(*size) += strlen;
		*ptr += strlen;
		if (!(new = create_part(str, ft_strlen(str))))
			exit(1);
		add_part(list, new);
	}
}

static void	parse_placeholder(char **ptr,
								int *size,
								t_part **list,
								va_list args)
{
	t_placeholder	ph;
	int				result;

	parse_flags(&(ph.flags), ptr);
	parse_width(&ph, ptr, args);
	parse_precision(&(ph.precision), ptr, args);
	parse_length(&(ph.length), ptr);
	if (**ptr)
	{
		parse_type(&ph, **ptr);
		ph.base = get_base(ph.type);
		result = handle_type(&ph, args, size, list);
		if (result == -1)
			*size = -1;
		else
			*size += result;
		(*ptr)++;
	}
}

t_part		*parse(int *size, char *ptr, va_list args)
{
	t_part	*list;

	list = NULL;
	while (*ptr && (*size != -1))
	{
		parse_str(&ptr, size, &list);
		if (*ptr)
		{
			ptr++;
			parse_placeholder(&ptr, size, &list, args);
		}
	}
	return (list);
}
