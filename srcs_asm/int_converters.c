#include "asm.h"

void 					int32_converter(t_cursor *p, unsigned size,
													t_int32 k, size_t ref_pos)
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
		if (ref_pos == 0)
			ft_vec_add(&(p->code), &octets[i]);
		else
			((uint8_t *)p->code->data)[ref_pos++] = octets[i];
		i--;
	}
	display_grid(p->code->data, p->code->total, -1);
}

int32_t					core_atoi(const char *str, size_t row, size_t col)
{
	int					sign;
	int64_t 			res;

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
		if ((sign == 1 && res > INT32_MAX)
			|| (sign == -1 && res - 2 >= INT32_MAX))
			lexical_error(row, col);
	}
	return ((int32_t)(res * sign));
}