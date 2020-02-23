#include "asm.h"
#include "dasm.h"

void 			print_lexical_tree(t_ins *root, char mod)
{
	t_lab		*lab;
	t_args		*arg;

	if (mod == 'f')
	{
		while (root->next)
			root = root->next;
	}
	while (root)
	{
		ft_printf("%s: (%d) ", g_op_tab[root->code - 1].name, root->bytes);
		lab = root->lab;
		while (lab)
		{
			ft_printf("{yellow}%s {eoc}", lab->name);
			lab = lab->next;
		}
		if (g_op_tab[root->code].args_type_code)
			ft_printf("(%08b) (%08b) (%08b)\n", root->type_code[0], root->type_code[1], root->type_code[2]);
		ft_printf("\n{red}%d: \t{eoc}|--", root->row);
		arg = root->args;
		while (arg)
		{
			ft_printf("{green}(%d)[{blue}%-4d]{eoc}", arg->size, arg->code);
//			else
//				ft_printf("%-4s ", arg->data);
			arg = arg->next;
		}
		ft_printf("\n");
		root = (mod == 'f') ? root->prev : root->next;
	}
}

void 					print_tokens(t_lex *l)
{
	while (l)
	{
		ft_printf("%3d : %3d \t", l->row + 1, l->col + 1);
		ft_printf("{red}[%s]{eoc} ", g_tokens[l->type]);
		ft_printf("%s\n", l->lex);
		l = l->next;
	}
}


void 			display_grid(uint8_t g[], unsigned size, size_t hl)
{
	int 		q;

	q = 0;
	while (q < size)
	{
		if ((q % 16) == 0)
			ft_printf("\n");
		if (hl == q)
			ft_printf("{red}%02x{eoc}", g[q]);
		else
			ft_printf("%02x", g[q]);
		if (q % 2)
			ft_printf("\t");
		q++;
	}
	ft_printf("\n---\n");
}

void 			display_collected(t_parser *p)
{
	int 		i;
	t_op 		*tmp;

	ft_printf("%s: %s\n", p->name, p->comment);
	tmp = p->ops;
	while (tmp)
	{
		ft_printf("{red}%s{eoc}\n", g_op_tab[tmp->op - 1].name);
		i = 0;
		while (tmp->args_type_code[i] && i < 3)
		{
			if (tmp->args_type_code[i] == REG_CODE)
				ft_printf("T_REG \t");
			if (tmp->args_type_code[i] == DIR_CODE)
				ft_printf("T_DIR \t");
			if (tmp->args_type_code[i] == IND_CODE)
				ft_printf("T_IND \t");
			i++;
		}
		ft_printf("\n");
		i = 0;
		while (i < g_op_tab[tmp->op - 1].args_num)
		{
			ft_printf("%d\t\t", tmp->args[i]);
			i++;
		}
		ft_printf("\n---\n");
		tmp = tmp->next;
	}
}
