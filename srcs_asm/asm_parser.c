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


void				asm_parser(char *path)
{
	t_cursor		*p;

    p = init_cursor(path);
	while (p->pos < p->file->total - 1 && skip_void(p))
		collect_lexemes(p);
	push_lexeme(p, EOF, NULL);
	syntaxer(p);
	analyzer(p);
	print_lexical_tree(p->root, 'f');
//	print_tokens(p->lex);
	free_all(p);
}
