/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 23:02:53 by ylila             #+#    #+#             */
/*   Updated: 2020/01/21 23:03:19 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static long long	make_result(const char *str, _Bool sign)
{
	long long res;
	long long max;

	res = 0;
	max = 9223372036854775807;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			if ((sign && (res <= ((max - (*str - '0')) / 10))) ||
				(!sign && (-res >= ((-max - 1 + (*str - '0')) / 10))))
				res = res * 10 + (*str - '0');
			else if (sign)
				return (-1);
			else if (!sign)
				return (0);
		}
		else
			break ;
		++str;
	}
	if (sign == 0)
		res = -res;
	return (res);
}

long long			ft_atol(const char *str)
{
	_Bool is_negative;

	is_negative = 1;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n' ||
					*str == '\r' || *str == '\f' || *str == '\v'))
		++str;
	if (*str == '-')
	{
		is_negative = 0;
		++str;
	}
	else if (*str == '+')
	{
		is_negative = 1;
		++str;
	}
	return (make_result(str, is_negative));
}
