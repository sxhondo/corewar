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

#include "asm.h"

int						core_atoi(const char *str, int *num, t_asm_parser *p)
{
	int					sign;
	long				res;
	int					i;

	i = 0;
	res = 0;
	sign = 1;
	if ((*str == '-' || *str == '+') && ++i)
		sign = *str++ == '-' ? -1 : 1;
	if (!ft_isdigit(*str))
		asm_error(BAD_NUM, p->row, p->col);
	while (*str && ft_isdigit(*str) && ++i)
	{
		if (!*str || *str < '0' || *str > '9')
			asm_error(BAD_NUM, p->row, p->col);
		res = res * 10 + (*str++ - '0');
		if ((sign == 1 && res > INT32_MAX)
			|| (sign == -1 && res - 2 >= INT32_MAX))
			asm_error(BAD_NUM, p->row, p->col);
	}
	*num = (int)(res * sign);
	return (i);
}

void            asm_error(int num, unsigned row, unsigned col)
{
	ft_fprintf(2, "error: ");
	ft_fprintf(2, "[%d][%d] ", row, col);
    ft_fprintf(2, "%s\n", errors[num]);
    exit (1);
}