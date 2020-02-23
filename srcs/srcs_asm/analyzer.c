/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:58:53 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 19:58:54 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"
#include "asm.h"

static int32_t		calc_size(t_ins *root, size_t row, t_lab *un)
{
	int32_t			res;

	res = 0;
	while (root && row--)
	{
		res += root->bytes;
		root = root->next;
	}
	while (un)
	{
		un->code_pos = res;
		un = un->next;
	}
	return (res);
}

static void			calculate_num(t_args *ar, t_ins *r)
{
	if ((ar->type == DIRECT || ar->type == DIRECT_LABEL)
		&& g_op_tab[r->code - 1].args_type_code)
		r->type_code[r->type_code_pos++] = DIR_CODE;
	else if ((ar->type == INDIRECT || ar->type == INDIRECT_LABEL)
										&& g_op_tab[r->code - 1].args_type_code)
		r->type_code[r->type_code_pos++] = IND_CODE;
	else if (ar->type == REGISTER && g_op_tab[r->code - 1].args_type_code)
		r->type_code[r->type_code_pos++] = REG_CODE;
	ar->code = core_atoi(ar->data);
}

static void			calculate_label(t_cursor *p, t_args *ar,
													t_ins *r, t_lab **u_labs)
{
	if (ar->type == DIRECT_LABEL && g_op_tab[r->code - 1].args_type_code)
		r->type_code[r->type_code_pos++] = DIR_CODE;
	else if (ar->type == INDIRECT_LABEL && g_op_tab[r->code - 1].args_type_code)
		r->type_code[r->type_code_pos++] = IND_CODE;
	ar->code = calculate_distance(p, r, ar->data);
	if (ar->code == -1)
	{
		add_label(u_labs, ar->data, 0);
		(*u_labs)->row = r->row;
		(*u_labs)->col = ar->col;
	}
}

void				analyzer(t_cursor *p)
{
	static t_lab	*u_labs = NULL;
	t_ins			*r;
	t_args			*ar;

	p->code_size = calc_size(p->root, p->row, p->lab);
	r = p->root;
	while (r)
	{
		if (!(ar = r->args))
			lexical_error(r->row, 0);
		while (ar)
		{
			if (ar->type == DIRECT || ar->type == INDIRECT ||
			ar->type == REGISTER)
				calculate_num(ar, r);
			else if (ar->type == DIRECT_LABEL || ar->type == INDIRECT_LABEL)
				calculate_label(p, ar, r, &u_labs);
			ar = ar->next;
		}
		r = r->next;
	}
	if (u_labs)
		undeclared_label_error(u_labs);
}
