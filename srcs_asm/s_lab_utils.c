#include "asm.h"

static t_lab 	*init_lab(char *name, unsigned row, unsigned col, size_t pos)
{
	t_lab		*l;

	if (!(l = ft_memalloc(sizeof(t_lab))))
		common_error(CANT_ALLOCATE);
	else
	{
		l->name = name;
		l->row = row;
		l->col = col;
		l->code_pos = pos;
	}
	return (l);
}

void 			push_label(t_asm_parser *p, t_lex *lx)
{
	t_lab		*tmp;
	t_lab		*lab;

	lab = init_lab(lx->lex, lx->row, lx->col, p->pos);
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


int32_t 			find_declared_labs(t_asm_parser *p, t_lab *lab, char *search)
{
	while (lab)
	{
		if (ft_strequ(lab->name, search))
			return (p->pos - lab->code_pos);
		lab = lab->next;
	}
	return (0);
}