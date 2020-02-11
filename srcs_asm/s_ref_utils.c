#include "asm.h"

void 			restore_ref(t_asm_parser *p, t_ref *ref)
{
	t_int32 	k;

	k.num = p->pos - p->ref->pos;
	ft_printf("diff is %d\n", k.num);
	ft_printf("ref: %s: was at [%d]\n", p->ref->name, p->ref->pos);
	ft_printf("curr at [%d]\n", p->pos);
	int32_converter(p, ref->size, k, p->ref->pos);
}

void 			push_ref(t_asm_parser *p, int32_t size, char *name)
{
	t_ref		*r;
	t_ref 		*tmp;

	if (!(r = ft_memalloc(sizeof(t_ref))))
		common_error(CANT_ALLOCATE);
	else
	{
		r->name = name;
		r->on = 1;
		r->pos = p->pos;
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
