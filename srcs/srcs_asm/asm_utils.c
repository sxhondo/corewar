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

int						is_argument(int type)
{
	return (type == DIRECT || type == DIRECT_LABEL || type == INDIRECT ||
		type == INDIRECT_LABEL || type == REGISTER);
}

int						is_separator(int a, uint8_t code)
{
	if (a < g_op_tab[code - 1].args_num)
		return (1);
	return (0);
}

static void				free_tree(t_ins *root)
{
	t_lab				*lab_next;
	t_ins				*op_next;
	t_args				*arg_next;

	while (root)
	{
		op_next = root->next;
		while (root->lab)
		{
			lab_next = root->lab->next;
			free(root->lab);
			root->lab = lab_next;
		}
		while (root->args)
		{
			arg_next = root->args->next;
			free(root->args);
			root->args = arg_next;
		}
		free(root);
		root = op_next;
	}
}

void					free_all(t_cursor *p)
{
	t_lab				*lab_next;
	t_lex				*lex_next;

	while (p->lab)
	{
		lab_next = p->lab->next;
		free(p->lab);
		p->lab = lab_next;
	}
	while (p->lex)
	{
		lex_next = p->lex->next;
		ft_strdel(&p->lex->lex);
		free(p->lex);
		p->lex = lex_next;
	}
	free_tree(p->root);
	ft_vec_del(&(p->file));
	close(p->fd);
	free(p);
}
