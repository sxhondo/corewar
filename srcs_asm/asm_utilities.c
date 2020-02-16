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
		ft_printf("%s: (%d) ", op_tab[root->code - 1].name, root->bytes);
		lab = root->lab;
		while (lab)
		{
			ft_printf("{yellow}%s{eoc}", lab->name);
			lab = lab->next;
		}
		ft_printf("\n\t|--");
		arg = root->args;
		while (arg)
		{
			if (arg->data && arg->code)
				ft_printf("{blue}%-4d {eoc}", arg->code);
			else
				ft_printf("%-4s ", arg->data);
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
		ft_printf("{red}[%s]{eoc} ", tokens[l->type]);
		ft_printf("%s\n", l->lex);
		l = l->next;
	}
}

void 					free_all(t_cursor *p)
{
	t_lab				*lab_next;
	t_lex				*lex_next;
	t_ins				*op_next;
	t_args				*arg_next;

	while (p->lex)
	{
		lex_next = p->lex->next;
		ft_strdel(&p->lex->lex);
		free(p->lex);
		p->lex = lex_next;
	}
	while (p->root)
	{
		op_next = p->root->next;
		while (p->root->lab)
		{
			lab_next = p->root->lab->next;
			free(p->root->lab);
			p->root->lab = lab_next;
		}
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