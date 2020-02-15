/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:46:09 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/27 14:46:10 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int32_t 		calculate_distance(t_op *root)
{
	size_t 			pos;

	pos = 0;
	while (root)
	{

		root = root->next;
	}


}

static void 		semantic_analyzer(t_cursor *p)
{
	t_op			*r;
	t_args			*ar;
	size_t 			code_p;

	code_p = 0;
	r = p->root;
	while (r)
	{
		ar = r->args;
		ft_printf("%s: ", op_tab[r->code - 1].name);
		while (ar)
		{
			if (ar->type == DIRECT || ar->type == INDIRECT || ar->type == REGISTER)
				ar->code = core_atoi(ar->data, ar);
			else if (ar->type == DIRECT_LABEL || ar->type == INDIRECT_LABEL)
				ar->code = calculate_distance(p->root);
			ft_printf("%s ", ar->data);
			ar = ar->next;
		}
		ft_printf("\n");
		r = r->next;
	}
}

void				asm_parser(char *path)
{
	t_cursor		*p;

    p = init_cursor(path);
	while (p->pos < p->file->total - 1)
	{
		skip_void(p);
		collect_lexemes(p);
	}
	push_lexeme(p, EOF, NULL);
	syntaxer(p);
//	semantic_analyzer(p);

//	print_labels(p->lab);
	print_lexical_tree(p->root);
//	print_tokens(p->lex);
	free_all(p);
}
