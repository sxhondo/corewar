#include "asm.h"

static t_lex	*init_lex(int type, char *lex, t_cursor *p)
{
	t_lex		*l;

	if (!(l = ft_memalloc(sizeof(t_lex))))
	{
		common_error(CANT_ALLOCATE);
		return (NULL);
	}
	l->type = type;
	l->row = p->row;
	l->col = p->col;
	l->lex = lex;
	return (l);
}

void 			push_lexeme(t_cursor *p, int type, char *lex)
{
	t_lex		*tmp;
	t_lex		*l;

	l = init_lex(type, lex, p);
	if (type == NL)
	{
		p->col = 0;
		p->row += 1;
	}
	tmp = p->lex;
	if (!p->lex)
		p->lex = l;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = l;
		l->next = NULL;
	}
}