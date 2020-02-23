/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 20:21:52 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 20:21:54 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		common_error(int num)
{
	ft_fprintf(2, "%s\n", g_errors[num]);
	exit(1);
}

void		lexical_error(unsigned row, unsigned col)
{
	ft_fprintf(2, "Lexical error at [%d:%d]\n", row + 1, col + 1);
	exit(2);
}

void		token_error(t_lex *lx, t_cursor *p)
{
	ft_fprintf(2, "%d:%d: "
"unexpected %s \"%s\"\n", lx->row + 1, lx->col + 1, g_tokens[lx->type],
lx->lex);
	free_all(p);
	exit(3);
}

void		argument_error(t_lex *lx, char *op)
{
	ft_fprintf(2, "%d:%d: "
"invalid argument %s \"%s\" for operator \"%s\"", lx->row + 1, lx->col + 1,
g_tokens[lx->type], lx->lex, op);
	exit(4);
}

void		undeclared_label_error(t_lab *lab)
{
	t_lab	*lab_next;

	while (lab)
	{
		lab_next = lab->next;
		ft_fprintf(2, "undeclared label \"%s\" at %d:%d\n",
			lab->name, lab->row + 1, lab->col + 1);
		ft_strdel(&lab->name);
		free(lab);
		lab = lab_next;
	}
	exit(5);
}
