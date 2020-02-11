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

static int32_t 		find_label_pos(t_lab *lab, char *search)
{
	while (lab)
	{
		if (ft_strequ(lab->name, search))
			return (lab->code_pos);
		lab = lab->next;
	}
	return (-1);
}

int32_t 			find_label_diff(t_lab *lab, char *search, size_t pos)
{
	int32_t			i;
	int32_t 		tmp;

	i = 0;
	if ((tmp = find_label_pos(lab, search)) == -1)
		return (-1);
	while (pos > tmp)
	{
		pos--;
		i--;
	}
	return (i);
}