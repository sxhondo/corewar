#include "asm.h"

static t_lab 	*init_lab(char *name, unsigned row, unsigned col)
{
	t_lab		*l;

	if (!(l = ft_memalloc(sizeof(t_lab))))
		common_error(CANT_ALLOCATE);
	else
	{
		l->name = name;
		l->row = row;
		l->col = col;
	}
	return (l);
}

void 			push_label(t_asm_parser *p, t_lex *lx)
{
	t_lab		*tmp;
	t_lab		*lab;

	lab = init_lab(lx->lex, lx->row, lx->col);
	tmp = p->lab;
	if (!p->lab)
		p->lab = lab;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lab;
		lab->next = NULL;
	}
}
