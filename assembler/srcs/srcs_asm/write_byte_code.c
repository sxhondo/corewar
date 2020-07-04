/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_byte_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 20:07:27 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 20:07:28 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			write_name(t_vec *code, const char *name)
{
	union u_int32	k;
	int				i;

	i = 0;
	while (name[i])
	{
		k.num = name[i];
		int32_converter(code, sizeof(uint8_t), k);
		i++;
	}
	write_null(code, PROG_NAME_LENGTH - i);
}

static void			write_comment(t_vec *code, const char *comment)
{
	union u_int32	k;
	int				i;

	i = 0;
	while (comment[i])
	{
		k.num = comment[i];
		int32_converter(code, sizeof(uint8_t), k);
		i++;
	}
	write_null(code, COMMENT_LENGTH - i);
}

static void			write_type_code(t_vec *code, uint8_t ins,
												const uint8_t atypes[])
{
	union u_int32	k;

	if (g_op_tab[ins - 1].args_type_code)
	{
		k.num = 0;
		k.bin.b4 = atypes[0];
		k.bin.b3 = atypes[1];
		k.bin.b2 = atypes[2];
		k.bin.b1 = 0;
		int32_converter(code, sizeof(uint8_t), k);
	}
}

static void			write_exec_code(t_ins *root, t_vec *code)
{
	t_ins			*r;
	t_args			*ar;
	t_int32			k;

	r = root;
	while (r && r->next)
		r = r->next;
	while (r)
	{
		k.num = r->code;
		int32_converter(code, sizeof(uint8_t), k);
		write_type_code(code, r->code, r->type_code);
		ar = r->args;
		while (ar)
		{
			k.num = ar->code;
			int32_converter(code, ar->size, k);
			ar = ar->next;
		}
		r = r->prev;
	}
}

t_vec				*write_code(t_cursor *p)
{
	union u_int32	k;
	t_vec			*code;

	if (!(code = ft_vec_init(1, sizeof(uint8_t))))
		common_error(CANT_ALLOCATE);
	k.num = COREWAR_EXEC_MAGIC;
	int32_converter(code, sizeof(uint32_t), k);
	write_name(code, p->name);
	write_null(code, sizeof(uint32_t));
	k.num = p->code_size;
	int32_converter(code, sizeof(uint32_t), k);
	write_comment(code, p->comment);
	write_null(code, sizeof(uint32_t));
	write_exec_code(p->root, code);
	if (!(code = ft_vec_resize(&code)))
		common_error(CANT_ALLOCATE);
	return (code);
}
