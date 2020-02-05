#include "asm.h"

static int			check_instruction(char *ins, t_asm_parser *p, int len)
{
	int 			i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(ins, op_tab[i].name))
			return (op_tab[i].code);
		i++;
	}
	asm_error(BAD_INSTRUCTION, p->row, p->col);
	return (-1);
}

static void 		collect_dir(t_ins *elem, t_asm_parser *p, int a)
{
	int 			i;

	p->pos += 1;
	if (!(op_tab[elem->code - 1].args_types[a] & T_DIR))
		asm_error(INVALID_ARGUMENT, p->row, p->col);
	if (p->f_data[p->pos] && p->f_data[p->pos] == ':')
	{
		i = 0;
		p->col += 1;
		p->pos += 1;
		while (p->f_data[p->pos + i] && is_label_char(p->f_data[p->pos + i]))
			i++;
		if (!(elem->largs[a] = ft_strndup(p->f_data + p->pos, i)))
			asm_error(CANT_ALLOCATE, 0, 0);
		p->pos += i;
	}
	else
		p->pos += core_atoi(p->f_data + p->pos, &(elem->args[a]), p);
}

static void 		collect_reg(t_ins *elem, t_asm_parser *p, int a)
{
	skip_tab_space(p);
	if (!(op_tab[elem->code - 1].args_types[a] & T_REG))
		asm_error(INVALID_ARGUMENT, p->row, p->col);
	p->pos += 1;
	p->pos += core_atoi(p->f_data + p->pos, &(elem->args[a]), p);
	if (elem->args[a] >= 1 && elem->args[a] <= 16)
		return ;
	else
		asm_error(REGISTER_OUT_OF_BOUNDS, p->row, p->col);
}

static void 		collect_ind(t_ins *elem, t_asm_parser *p, int a)
{
	skip_tab_space(p);
	if (!(op_tab[elem->code - 1].args_types[a] & T_IND))
		asm_error(INVALID_ARGUMENT, p->row, p->col);
	p->pos += core_atoi(p->f_data + p->pos, &(elem->args[a]), p);

}

static void			args_parser(t_asm_parser *p, t_ins *elem)
{
	int 			a;

	a = -1;
	while (++a < op_tab[elem->code - 1].args_num)
	{
		skip_separator(p, elem, a);
		if (p->f_data[p->pos] == '%')
			collect_dir(elem, p, a);
		else if (p->f_data[p->pos] == 'r')
			collect_reg(elem, p, a);
		else if (is_num(p->f_data[p->pos]))
			collect_ind(elem, p, a);
		else
			asm_error(INVALID_SYNTAX, p->row, p->col);
	}
}

void 				ins_parser(t_asm_parser *p, t_label *lab, t_ins **ins)
{
	t_ins			*elem;
	char 			*name;
	int 			i;

	i = 0;
	while (p->f_data[p->pos + i] && ft_isalpha(p->f_data[p->pos + i]))
		i++;
	if ((name = ft_strndup(p->f_data + p->pos, i)) == NULL)
		asm_error(CANT_ALLOCATE, 0, 0);
	elem = init_ins(name, p->row, p->col);
	elem->code = check_instruction(name, p, i);
	elem->labels = lab;
	p->col += i;
	p->pos += i;
	args_parser(p, elem);
	push_back_ins(ins, elem);
	ft_strdel(&name);
}