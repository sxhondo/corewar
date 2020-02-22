/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:05:03 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/27 14:05:04 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include "asm.h"

void				asm_parser(char *path)
{
	t_cursor		*p;

	p = init_cursor(path);
	while (p->pos < p->file->total)
		lexer(p);
	syntaxer(p);
	analyzer(p);
//	print_lexical_tree(p->root, 'f');
	p->code = write_code(p);
	write_in_file(p->code, path);
	free_all(p);
}