#include "asm.h"

static void 			write_type_arg(t_asm_parser *p, t_op_tab op, const uint8_t atypes[])
{
	t_int32				k;

	if (op.args_type_code)
	{
		k.num = 0;
		k.bin.b3 = atypes[0];
		k.bin.b2 = atypes[1];
		k.bin.b1 = atypes[2];
		int32_converter(p, sizeof(uint8_t), k, 0);

		ft_printf("t_arg: %08b\n", ((uint8_t *)p->code->data)[p->code->total - 1]);

		p->pos += sizeof(uint8_t);
	}
	display_grid(p->code->data, p->code->total, p->code->total - 1);
}

void 					write_arguments(const uint8_t atypes[], const int32_t arg[],
												t_asm_parser *p, t_op_tab op)
{
	int 				i;
	t_int32				k;


	i = -1;
	write_type_arg(p, op, atypes);
	while (++i < op.args_num)
	{
		k.num = arg[i];
		if (atypes[i] == T_DIR)
		{
			int32_converter(p, op.t_dir_size, k, 0);
			p->pos += op.t_dir_size + 1;

			/* *** */
			ft_printf("t_dir: [%08b]", ((uint8_t *)p->code->data)[p->code->total - 1]);
			display_grid(p->code->data, p->code->total, p->code->total - 1);
			/* *** */
		}
		if (atypes[i] == T_REG)
		{
			int32_converter(p, sizeof(uint8_t), k, 0);
			p->pos += sizeof(uint8_t) + 1;

			/* *** */
			ft_printf("t_reg: [%08b]", ((uint8_t *)p->code->data)[p->code->total - 1]);
			display_grid(p->code->data, p->code->total, p->code->total - 1);
			/* *** */
		}
		if (atypes[i] == T_IND)
		{
			int32_converter(p, sizeof(uint16_t), k, 0);
			p->pos += sizeof(uint16_t) + 1;

			/* *** */
			ft_printf("t_ind: [%08b]", ((uint8_t *)p->code->data)[p->code->total - 1]);
			display_grid(p->code->data, p->code->total, p->code->total - 1);
			/* *** */
		}
	}
}

void 					int32_converter(t_asm_parser *p, unsigned size,
													t_int32 k, size_t ref_pos)
{
	size_t				i;
	uint8_t 			octets[4];

	octets[3] = k.octets.o4;
	octets[2] = k.octets.o3;
	octets[1] = k.octets.o2;
	octets[0] = k.octets.o1;
/*
	for (int q = 0; q < 4; q++)
		ft_printf("%08b ", t[q]);
	ft_printf("\n");
*/
	i = size - 1;
	while (size--)
	{
//		ft_printf("%08b\n", t[i]);
		if (ref_pos == 0)
			ft_vec_add(&(p->code), &octets[i]);
		else
			((uint8_t *)p->code->data)[ref_pos++] = octets[i];
		i--;
	}
	display_grid(p->code->data, p->code->total, -1);
}