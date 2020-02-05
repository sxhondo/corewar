/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:51:56 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/27 14:51:57 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void 			print_label(t_label *l)
{
	while (l)
	{
		ft_printf("{yellow} %s %d : %d{eoc} ", l->lab, l->row, l->col);
		l = l->next;
	}
}

void 					print_collected(t_ins *ins)
{
	int 				a;

	while (ins)
	{
		ft_printf("%d:%d ", ins->row, ins->col);
		ft_printf("%#x [%s] ( ", ins->code, op_tab[ins->code - 1].name);
		a = 0;
		while (a < 3)
		{
			if (ins->largs[a] != NULL)
				ft_printf("%s ", ins->largs[a]);
			else
				ft_printf("%d ", ins->args[a]);
			a++;
		}
		ft_printf(")");
		print_label(ins->labels);
		ins = ins->next;
		ft_printf("\n");
	}
}

void 					free_all(t_asm_parser *p, t_ins *ins)
{
	t_ins				*ni;
	t_label				*nl;
	int 				i;

	while (ins)
	{
		ni = ins->next;
		while (ins->labels)
		{
			nl = ins->labels->next;
			ft_strdel(&ins->labels->lab);
			free(ins->labels);
			ins->labels = nl;
		}
		i = -1;
		while (++i < 3)
			ft_strdel(&ins->largs[i]);
		free(ins);
		ins = ni;
	}
	close(p->fd);
	ft_strdel(&(p->name));
	ft_strdel(&(p->comment));
	ft_vec_del(&(p->file));
	free(p);
}

int						core_atoi(const char *str, int *num, t_asm_parser *p)
{
	int					sign;
	long				res;
	int					i;

	i = 0;
	res = 0;
	sign = 1;
	if ((*str == '-' || *str == '+') && ++i)
		sign = *str++ == '-' ? -1 : 1;
	if (!ft_isdigit(*str))
		asm_error(INVALID_NUM, p->row, p->col);
	while (*str && ft_isdigit(*str) && ++i)
	{
		if (!*str || *str < '0' || *str > '9')
			asm_error(INVALID_NUM, p->row, p->col);
		res = res * 10 + (*str++ - '0');
		if ((sign == 1 && res > INT32_MAX)
			|| (sign == -1 && res - 2 >= INT32_MAX))
			asm_error(INVALID_NUM, p->row, p->col);
	}
	*num = (int)(res * sign);
	return (i);
}

void            asm_error(int num, unsigned row, unsigned col)
{
	ft_fprintf(2, "error: ");
	ft_fprintf(2, "[%d][%d] ", row, col);
    ft_fprintf(2, "%s\n", errors[num]);
    exit (1);
}