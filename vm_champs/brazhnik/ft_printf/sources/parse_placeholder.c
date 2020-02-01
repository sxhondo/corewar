/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_placeholder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 17:38:45 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/01 17:38:45 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

void	parse_flags(uint8_t *flags, char **ptr)
{
	int i;

	i = 0;
	*flags = 0b00000000;
	while (i < (int)(sizeof(g_flag) / sizeof(t_flag)))
	{
		if (**ptr == g_flag[i].flag)
		{
			*flags |= g_flag[i].code;
			(*ptr)++;
			i = 0;
		}
		else
			i++;
	}
}

void	parse_width(t_placeholder *ph, char **ptr, va_list args)
{
	ph->width = 0;
	if (ft_isdigit(**ptr))
	{
		ph->width = ft_atoi(*ptr);
		*ptr += ft_unsignedlen((uintmax_t)ph->width, 10);
	}
	if (**ptr == '*')
	{
		(*ptr)++;
		ph->width = va_arg(args, int);
		if (ph->width < 0)
		{
			ph->width = FT_ABS(ph->width);
			ph->flags |= MINUS;
		}
	}
	if (ft_isdigit(**ptr))
	{
		ph->width = ft_atoi(*ptr);
		*ptr += ft_unsignedlen((uintmax_t)ph->width, 10);
	}
}

void	parse_precision(int *precision, char **ptr, va_list args)
{
	*precision = -1;
	if (**ptr == '.')
	{
		*precision = 0;
		(*ptr)++;
		if (ft_isdigit(**ptr))
		{
			*precision = ft_atoi(*ptr);
			*ptr += ft_unsignedlen((uintmax_t)*precision, 10);
		}
		else if (**ptr == '*')
		{
			(*ptr)++;
			*precision = va_arg(args, int);
			*precision = (*precision < 0) ? -1 : *precision;
		}
	}
}

void	parse_length(uint8_t *length, char **ptr)
{
	*length = 0;
	if (**ptr == 'l' && (*ptr)++)
	{
		*length = LENGTH_L;
		if ((**ptr == 'l') && (*length == LENGTH_L) && (*ptr)++)
			*length = LENGTH_LL;
	}
	else if (**ptr == 'h' && (*ptr)++)
	{
		*length = LENGTH_H;
		if ((**ptr == 'h') && (*length == LENGTH_H) && (*ptr)++)
			*length = LENGTH_HH;
	}
	else if ((**ptr == 'j') && (*ptr)++)
		*length = LENGTH_J;
	else if ((**ptr == 'z') && (*ptr)++)
		*length = LENGTH_Z;
	else if ((**ptr == 'L') && (*ptr)++)
		*length = LENGTH_BIG_L;
	else if ((**ptr == 't') && (*ptr)++)
		*length = LENGTH_T;
	if ((**ptr == 'l') || (**ptr == 'h') || (**ptr == 'j') ||
		(**ptr == 'z') || (**ptr == 'L') || (**ptr == 't'))
		parse_length(length, ptr);
}

void	parse_type(t_placeholder *ph, char type)
{
	if (type == 'D' || type == 'O' || type == 'U')
	{
		if (ph->length != LENGTH_LL)
			ph->length = LENGTH_L;
		ph->type = (char)ft_tolower(type);
	}
	else if (type == 'X' || type == 'B' || type == 'F'
		|| type == 'E' || type == 'G' || type == 'A')
	{
		ph->flags |= UPPER;
		ph->type = (char)ft_tolower(type);
	}
	else if ((type == 's' || type == 'c') && ph->length == LENGTH_L)
		ph->type = (char)ft_toupper(type);
	else
		ph->type = type;
}
