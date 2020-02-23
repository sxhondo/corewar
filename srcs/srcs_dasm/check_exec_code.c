/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:21:13 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 19:21:14 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

static void				get_args_type(t_op *op, t_parser *p, const uint8_t code)
{
	int					i;
	t_int32				k;

	k.num = 0;
	if (g_op_tab[op->op - 1].args_type_code == 1)
	{
		k.num = code;
		op->args_type_code[0] = k.bin.b4;
		op->args_type_code[1] = k.bin.b3;
		op->args_type_code[2] = k.bin.b2;
		i = -1;
		while (++i < 3)
		{
			if (op->args_type_code[i] != 0
				&& op->args_type_code[i] != REG_CODE
				&& op->args_type_code[i] != DIR_CODE
				&& op->args_type_code[i] != IND_CODE)
				d_error(INVALID_TYPE_ARG);
		}
		p->pos += 1;
	}
	else
		op->args_type_code[0] = DIR_CODE;
}

static void				get_arguments(t_parser *p, t_op *elem, uint8_t code[])
{
	int					i;
	int					arg_size;
	int					arg_amount;

	arg_amount = g_op_tab[elem->op - 1].args_num;
	i = -1;
	while (++i < arg_amount)
	{
		arg_size = get_size(elem->args_type_code[i], elem->op);
		if (elem->args_type_code[i] == REG_CODE)
			elem->args[i] = get_reg(code, p->pos);
		if (elem->args_type_code[i] == DIR_CODE)
			elem->args[i] = get_dir_undir(code, p->pos, arg_size);
		if (elem->args_type_code[i] == IND_CODE)
			elem->args[i] = get_dir_undir(code, p->pos, arg_size);
		p->pos += arg_size;
	}
}

void					check_exec_code(t_parser *p)
{
	uint8_t				b[p->exe_code_size];
	t_op				*elem;

	if ((read(p->fd, &b, p->exe_code_size)) != p->exe_code_size)
		d_error(INVALID_FILE);
	while (p->pos < p->exe_code_size)
	{
		elem = init_operation();
		elem->op = b[p->pos++];
		if (elem->op < 0x01 || elem->op > 0x10)
			d_error(INVALID_OP_NAME);
		get_args_type(elem, p, b[p->pos]);
		get_arguments(p, elem, b);
		add_operation(&(p->ops), elem);
	}
}
