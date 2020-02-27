/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_rounding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:07:35 by ylila             #+#    #+#             */
/*   Updated: 2019/12/10 22:28:09 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_float.h"
#include "libft.h"

static void	nine_rounding(t_result *res, size_t i)
{
	while (*(res->result + res->len - i) == '9' ||
		*(res->result + res->len - i) == '.')
	{
		if (*(res->result + res->len - i) == '.')
		{
			++i;
			continue ;
		}
		*(res->result + res->len - i++) = '0';
	}
	++*(res->result + res->len - i);
}

void		float_round(t_result *res, const int nxt_nu)
{
	size_t	i;
	int		nu;

	i = 0;
	if (*(res->result + res->len - (++i)) == '.')
		++i;
	if (nxt_nu == 5 && *(res->result + res->len - 1) == '.')
	{
		nu = ft_atoi(res->result + res->len - i);
		if (nu == 9)
		{
			*(res->result + res->len - i) = '0';
			while (*(res->result + res->len - ++i) == '9')
				*(res->result + res->len - i) = '0';
			++*(res->result + res->len - i);
		}
		else if (nu % 2)
			++*(res->result + res->len - i);
	}
	else
		nine_rounding(res, i);
}
