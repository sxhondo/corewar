#include "asm.h"

void 			print_ref(t_ref *r)
{
	while (r)
	{
		ft_printf("on: %d, op_pos: %d, ex_pos: %d\n", r->on, r->op_pos, r->exact_pos);
		ft_printf("%s", r->name);
		r = r->next;
	}
}

void 			check_unused_refs(t_cursor *p, t_ref *r, t_lab *lab)
{
	t_int32		k;
	t_lab		*l;

	while (r)
	{
		l = lab;
		while (l)
		{
			if (ft_strequ(r->name, l->name))
			{
				k.num = l->code_pos - r->op_pos;
				int32_converter(p, r->size, k, r->exact_pos);
				display_grid(p->code->data, p->code->total, -1);
				break ;
			}
			l = l->next;
		}
		if (l == NULL)
			undeclared_label_error(r);
		r = r->next;
	}
}

void 			push_ref(t_cursor *p, t_lex *lx, int32_t size, size_t ex_pos)
{
	t_ref		*r;
	t_ref 		*tmp;

	if (!(r = ft_memalloc(sizeof(t_ref))))
		common_error(CANT_ALLOCATE);
	else
	{
		r->on = 0;
		r->col = lx->col;
		r->row = lx->row;
		r->name = lx->lex;
		r->op_pos = p->pos;
		r->exact_pos = ex_pos;
		r->size = size;
		tmp = p->ref;
		if (!p->ref)
			p->ref = r;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = r;
			r->next = NULL;
		}
	}
}
