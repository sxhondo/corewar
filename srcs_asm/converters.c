#include "asm.h"

static void 			write_byte(const uint8_t tmp[], t_asm_parser *p)
{
	t_int32 			k;

	k.num = 0;
	k.bin.b1 = tmp[0];
	k.bin.b2 = tmp[1];
	k.bin.b3 = tmp[2];
	int32_converter(p, sizeof(uint8_t), k);
}

void 					args_type_converter(t_lex *lx, t_op_tab o, t_asm_parser *p)
{
	uint8_t				tmp[3] = {0, 0, 0};
	int 				i;

	i = 0;
	while (i < o.args_num)
	{
		if (lx->type == REGISTER)
			tmp[i] = 0b00000001;
		if (lx->type == DIRECT || lx->type == DIRECT_LABEL)
			tmp[i] = 0b00000010;
		if (lx->type == INDIRECT || lx->type == INDIRECT_LABEL)
			tmp[i] = 0b00000011;
		lx = lx->next;
		i++;
		if (lx->type == SEPARATOR)
		{
			lx = lx->next;
			continue ;
		}
	}
	write_byte(tmp, p);
}

void 					int32_converter(t_asm_parser *p, unsigned size, t_int32 k)
{
	uint8_t 			tmp;

	p->pos += size;
	while (size)
	{
		if (size == 4)
			tmp = k.octets.o4;
		else if (size == 3)
			tmp = k.octets.o3;
		else if (size == 2)
			tmp = k.octets.o2;
		else
			tmp = k.octets.o1;
		ft_vec_add(&(p->code), &tmp);
//		ft_printf("%d written", tmp);
		k.octets.o4 = k.octets.o3;
		k.octets.o3 = k.octets.o2;
		k.octets.o2 = k.octets.o1;
		k.octets.o1 = 0;
		size--;
	}
}