#include "asm.h"

static int32_t 		calc_size(t_ins *root, size_t row)
{
	int32_t 		res;

	res = 0;
	while (root && row--)
	{
		res += root->bytes;
		root = root->next;
	}
	return (res);
}

static int32_t 		search_label(t_ins *root, char *search, int mod)
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
	return (-1);
}

static int 			handle_un_lab(t_cursor *p, char *search)
{
	t_lab			*l;

	l = p->lab;
	while (l)
	{
		if (ft_strequ(l->name, search))
			return (1);
		l = l->next;
	}
	return (0);
}

static int32_t		calculate_distance(t_cursor  *p, t_ins *curr, char *search, size_t col)
{
	t_ins			*rev;
	int32_t 		a;

	if ((a = search_label(curr->next, search, 0)) == -1)
	{
		rev = curr;
		while (rev->next)
			rev = rev->next;
		while (rev && rev->row != curr->row)
			rev = rev->prev;
		if ((a = search_label(rev, search, 1)) == -1
			&& !handle_un_lab(p, search))
			undeclared_label_error(search, curr->row, col);
	}
	return (a);
}

void 				analyzer(t_cursor *p)
{
	t_ins			*r;
	t_args			*ar;

	p->code_size = calc_size(p->root, p->row);
	r = p->root;
	while (r)
	{
		ar = r->args;
//		ft_printf("%s: ", op_tab[r->code - 1].name);
		while (ar)
		{
			if (ar->type == DIRECT || ar->type == INDIRECT || ar->type == REGISTER)
				ar->code = core_atoi(ar->data, r->row, ar->col);
			else if (ar->type == DIRECT_LABEL || ar->type == INDIRECT_LABEL)
				ar->code = calculate_distance(p, r, ar->data, ar->col);
//			ft_printf("%d", ar->code);
			ar = ar->next;
		}
		r = r->next;
	}

}
