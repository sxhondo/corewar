#include "asm.h"
/*
 * 	11111111
	00001001
	00000001
	11111010
 */
void 					int32_converter(t_vec *code, unsigned size, t_int32 k)
{
	size_t				i;
	uint8_t 			octets[4];

	octets[3] = k.octets.o4;
	octets[2] = k.octets.o3;
	octets[1] = k.octets.o2;
	octets[0] = k.octets.o1;
	i = size - 1;
	while (size--)
	{
		ft_vec_add(&code, &octets[i]);
		i--;
	}
//	display_grid(code->data, code->total, -1);
}

int64_t					core_atoi(const char *str, size_t row, size_t col)
{
	int					sign;
	uint64_t			res;

	res = 0;
	sign = 1;
	if ((*str == '-' || *str == '+'))
		sign = *str++ == '-' ? -1 : 1;
	if (!ft_isdigit(*str))
		lexical_error(row, col);
	while (*str && ft_isdigit(*str))
	{
		if (!*str || *str < '0' || *str > '9')
			lexical_error(row, col);
		res = res * 10 + (*str++ - '0');
		if ((sign == 1 && res > INT64_MAX))
			return (-1);
		if ((sign == -1 && res - 2 >= INT64_MAX))
			return (0);
	}
	return ((int64_t)(res * sign));
}