#include "asm.h"

void 		push_back_ins(t_ins **dst, t_ins *elem)
{
	t_ins	*tmp;

	tmp = *dst;
	if (!*dst)
		*dst = elem;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
		elem->next = NULL;
		elem->prev = tmp;
	}
}

t_ins 		*init_ins(char *name, unsigned row, unsigned col)
{
	t_ins	*elem;

	if (!(elem = ft_memalloc(sizeof(t_ins))))
		asm_error(CANT_ALLOCATE, 0, 0);
	else
	{
		elem->col = col;
		elem->row = row;
	}
	return (elem);
}