#include <general.h>
#include "asm.h"

static int32_t 		calc_size(t_ins *root, size_t row, t_lab *un)
{
	int32_t 		res;

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

static int32_t 		check_empty_labels(t_lab *l, char *search, int32_t pos)
{
	while (l)
	{
		if (ft_strequ(l->name, search))
			return (pos);
		l = l->next;
	}
	return (-1);
}

static int32_t 		search_label(t_ins *root, t_lab *un, char *search, int mod)
{
	t_lab			*l;
	t_ins 			*r;
	int32_t 		pos;

	pos = 0;
	r = root;
	while (r)
	{
		l = r->lab;
		while (l)
		{
			if (ft_strequ(l->name, search))
				return (mod == 0 ? -(pos + r->bytes) : pos);
			l = l->next;
		}
		pos += r->bytes;
		r = mod == 0 ? r->next : r->prev;
	}
	return (mod == 0 ? -1 : check_empty_labels(un, search, pos));
}

static int32_t		calculate_distance(t_cursor *p, t_ins *curr, char *search, size_t col)
{
	t_ins			*rev;
	int32_t 		a;

	if ((a = search_label(curr->next, p->lab, search, 0)) == -1)
	{
		rev = curr;
		while (rev->next)
			rev = rev->next;
		while (rev && rev->row != curr->row)
			rev = rev->prev;
		a = search_label(rev, p->lab, search, 1);
	}
	return (a);
}

static void 		add_invalid_label(t_lab **u_labs, char *name,
														size_t row, size_t col)
{
	add_label(u_labs, name, 0);
	(*u_labs)->row = row;
	(*u_labs)->col = col;
}

static void 		calculate_num(t_args *ar, t_ins *r)
{
	if ((ar->type == DIRECT || ar->type == DIRECT_LABEL)
		&& op_tab[r->code - 1].args_type_code)
		r->type_code[r->type_code_pos++] = DIR_CODE;
	else if ((ar->type == INDIRECT || ar->type == INDIRECT_LABEL)
										&& op_tab[r->code - 1].args_type_code)
		r->type_code[r->type_code_pos++] = IND_CODE;
	else if (ar->type == REGISTER && op_tab[r->code - 1].args_type_code)
		r->type_code[r->type_code_pos++] = REG_CODE;
	ar->code = core_atoi(ar->data, r->row, ar->col);
}

static void 		calculate_label(t_cursor *p, t_args *ar, t_ins *r, t_lab *u_labs)
{
	if (ar->type == DIRECT_LABEL && op_tab[r->code - 1].args_type_code)
		r->type_code[r->type_code_pos++] = DIR_CODE;
	else if (ar->type == INDIRECT_LABEL && op_tab[r->code - 1].args_type_code)
		r->type_code[r->type_code_pos++] = IND_CODE;
	ar->code = calculate_distance(p, r, ar->data, ar->code);
	if (ar->code == -1)
		add_invalid_label(&u_labs, ar->data, r->row, ar->col);
}

void 				analyzer(t_cursor *p)
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
			if (ar->type == DIRECT || ar->type == INDIRECT || ar->type == REGISTER)
				calculate_num(ar, r);
			else if (ar->type == DIRECT_LABEL || ar->type == INDIRECT_LABEL)
				calculate_label(p, ar, r, u_labs);
			ar = ar->next;
		}
		r = r->next;
	}
	if (u_labs)
		undeclared_label_error(u_labs);
}
