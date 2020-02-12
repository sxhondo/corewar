#include "asm.h"

void 					int32_converter(t_asm_parser *p, unsigned size,
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