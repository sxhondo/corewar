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

	if ((type != NL && type != SEPARATOR && type != EOF) && lex == NULL)
		common_error(CANT_ALLOCATE);
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

void 			add_label(t_lab **dst, t_lex *lx)
{
	t_lab		*elem;

	if (!(elem = ft_memalloc(sizeof(t_lab))))
		common_error(CANT_ALLOCATE);
	else
	{
		elem->name = lx->lex;
		elem->row = lx->row;
		elem->next = *dst;
		*dst = elem;
	}
}

void 		push_back_argument(t_args **dst, t_lex *lex)
{
	t_args 	*tmp;
	t_args	*elem;

	if (!(elem = ft_memalloc(sizeof(t_args))))
		common_error(CANT_ALLOCATE);
	else
	{
		elem->type = lex->type;
		elem->data = lex->lex;
		elem->col = lex->col;
		if (!*dst)
			*dst = elem;
		else
		{
			tmp = *dst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = elem;
			elem->next = NULL;
		}
	}
}

void 		add_ins(t_ins **dst, t_lex *curr, t_lab *lab)
{
	t_ins	*elem;

	if (!(elem = ft_memalloc(sizeof(t_ins))))
		common_error(CANT_ALLOCATE);
	else
	{
		elem->lab = lab;
		elem->row = curr->row;
		elem->code = get_operator(curr->lex);
		elem->bytes = op_tab[elem->code - 1].args_type_code ? 2 : 1;
		if (*dst)
			(*dst)->prev = elem;
		elem->next = *dst;
		*dst = elem;
	}
}
