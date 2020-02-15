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

void 			print_lexical_tree(t_op *root)
{
	t_args		*arg;
	t_lab		*lab;


	while (root)
	{
		ft_printf("%s: (b_size: %d)", op_tab[root->code - 1].name, root->bytes);
		ft_printf("lab: ");
		lab = root->labels;
		while (lab)
		{
			ft_printf("%s", lab->name);
			lab = lab->next;
		}
		ft_printf("\n\t|--");
		arg = root->args;
		while (arg)
		{
			ft_printf("%-4s ", arg->data);
			arg = arg->next;
		}
		ft_printf("\n");
		root = root->next;
	}
}

void 					print_labels(t_lab *l)
{
	while (l)
	{
		ft_printf("%d:%d {yellow}%d %s{eoc}\n", l->row + 1, l->col + 1,
				l->code_pos, l->name);
		l = l->next;
	}
}

void 					print_tokens(t_lex *l)
{
	while (l)
	{
		ft_printf("%3d : %3d \t", l->row + 1, l->col + 1);
		ft_printf("{red}[%s]{eoc} ", tokens[l->type]);
		ft_printf("%s\n", l->lex);
		l = l->next;
	}
}

void 					free_all(t_cursor *p)
{
	t_lab				*lab_next;
	t_lex				*lex_next;
	t_ref 				*ref_next;
	t_op				*op_next;
	t_args				*arg_next;

	while (p->lex)
	{
		lex_next = p->lex->next;
		ft_strdel(&p->lex->lex);
		free(p->lex);
		p->lex = lex_next;
	}
	while (p->lab)
	{
		lab_next = p->lab->next;
		free(p->lab);
		p->lab = lab_next;
	}
	while (p->ref)
	{
		ref_next = p->ref->next;
		free(p->ref);
		p->ref = ref_next;
	}
	while (p->root)
	{
		op_next = p->root->next;
		while (p->root->args)
		{
			arg_next = p->root->args->next;
			free(p->root->args);
			p->root->args = arg_next;
		}
		free(p->root);
		p->root = op_next;
	}
	ft_vec_del(&(p->code));
	ft_vec_del(&(p->file));
	close(p->fd);
	free(p);
}

//t_lex 				*skip_nl(t_lex *lx)
//{
//	while (lx->type == NL)
//		lx = lx->next;
//	return (lx);
//}

int32_t					core_atoi(const char *str, t_args *ar)
{
	int					sign;
	int32_t 			res;

	res = 0;
	sign = 1;
	if ((*str == '-' || *str == '+'))
		sign = *str++ == '-' ? -1 : 1;
	if (!ft_isdigit(*str))
		lexical_error(ar->row, ar->col);
	while (*str && ft_isdigit(*str))
	{
		if (!*str || *str < '0' || *str > '9')
			lexical_error(ar->row, ar->col);
		res = res * 10 + (*str++ - '0');
		if ((sign == 1 && res > INT32_MAX)
			|| (sign == -1 && res - 2 >= INT32_MAX))
			lexical_error(ar->row, ar->col);
	}
	return ((int32_t)(res * sign));
}