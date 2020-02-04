#include <asm.h>

void 			print_label(t_label *l)
{
	while (l)
	{
		ft_printf("[%s] %d : %d\n", l->lab, l->row, l->col);
		l = l->next;
	}
}

void			add_label(t_label **dst, t_label *elem)
{
	if (elem)
	{
		elem->next = *dst;
		*dst = elem;
	}
}

t_label 		*init_label(char *str, int len, t_asm_parser *p)
{
	t_label		*elem;

	if ((elem = ft_memalloc(sizeof(t_label))) == NULL)
		asm_error(CANT_ALLOCATE, 0, 0);
	elem->col = p->col;
	elem->row = p->row;
	if ((elem->lab = ft_strndup(str, len)) == NULL)
		asm_error(CANT_ALLOCATE, 0, 0);
	return (elem);
}
