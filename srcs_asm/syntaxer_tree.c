#include "asm.h"

void 		collect_name(t_cursor *p)
{
	skip_nl(p);
	while (p->name == NULL || p->comment == NULL)
	{
		if (p->lex->next->type != STRING)
			token_error(p->lex->next);
		if (ft_strequ(p->lex->lex, NAME_CMD_STRING))
		{
			p->name = p->lex->next->lex;
			if (ft_strlen(p->name) > PROG_NAME_LENGTH)
				common_error(NAME_TOO_BIG);
		}
		else if (ft_strequ(p->lex->lex, COMMENT_CMD_STRING))
		{
			p->comment = p->lex->next->lex;
			if (ft_strlen(p->comment) > COMMENT_LENGTH)
				common_error(COMM_TOO_BIG);
		}
		p->lex = p->lex->next->next;
		if (p->lex->type != NL)
			token_error(p->lex);
		p->lex = p->lex->next;
	}
}

void 		add_operator(t_op **dst, t_lex *curr)
{
	t_op 	*tmp;
	t_op	*elem;

	if (!(elem = ft_memalloc(sizeof(t_op))))
		common_error(CANT_ALLOCATE);
	else
	{
		elem->code = get_operator(curr->lex);
		elem->bytes = op_tab[elem->code - 1].args_type_code ? 2 : 1;
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

void 		push_argument(t_args **dst, t_lex *lex)
{
	t_args 	*tmp;
	t_args	*new;

	if (!(new = ft_memalloc(sizeof(t_args))))
		common_error(CANT_ALLOCATE);
	else
	{
		new->type = lex->type;
		new->data = lex->lex;
		new->row = lex->row;
		new->col = lex->col;
		if (!*dst)
			*dst = new;
		else
		{
			tmp = *dst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
			new->next = NULL;
		}
	}
}

int32_t 			get_arg_size(t_lex *lx, t_op *root)
{
	if (lx->type == REGISTER)
	{
		return (sizeof(uint8_t));
	}
	else if (lx->type == INDIRECT || lx->type == INDIRECT_LABEL)
	{
		return (sizeof(uint16_t));
	}
	else if (lx->type == DIRECT || lx->type == DIRECT_LABEL)
	{
		return (op_tab[root->code - 1].t_dir_size);
	}
	return (-1);
}

void 			collect_arguments(t_cursor *p, t_op *root)
{
	p->lex = p->lex->next;
	while (p->lex->type != NL)
	{
		if (p->lex->type == DIRECT || p->lex->type == DIRECT_LABEL
		|| p->lex->type == INDIRECT || p->lex->type == INDIRECT_LABEL
			|| p->lex->type  == REGISTER)
		{
			while (root->next)
				root = root->next;
			root->bytes += get_arg_size(p->lex, root);
			push_argument(&root->args, p->lex);
		}
		else if (p->lex->type == SEPARATOR)
		{
			p->lex = p->lex->next;
			continue ;
		}
		else
			token_error(p->lex);
		p->lex = p->lex->next;
	}
}

void 			push_label(t_cursor *p, t_lex *lx)
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


void 			syntaxer(t_cursor *p)
{
	t_lab		*lab;
	t_op 		*root = NULL;
	t_lex		*head;

	head = p->lex;
	collect_name(p);
	while (p->lex->type != EOF)
	{
		skip_nl(p);
		if (p->lex->type == INSTRUCTION)
		{
			add_operator(&root, p->lex);
			collect_arguments(p, root);
		}
		else if (p->lex->type == LABEL)
			push_label(p->lab, p->lex);
		else
			token_error(p->lex);
		p->lex = p->lex->next;
	}
	p->lex = head;
	p->root = root;
}