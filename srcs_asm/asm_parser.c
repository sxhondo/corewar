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

void 				skip_empty_space(t_asm_parser *p)
{
	while (p->pos < p->file->total)
	{
		if (p->f_data[p->pos] == COMMENT_CHAR
			|| p->f_data[p->pos] == ALT_COMMENT_CHAR)
		{
			while (p->f_data[p->pos] && p->f_data[p->pos] != '\n')
				p->pos += 1;
		}
		if (p->f_data[p->pos] == ' ' || p->f_data[p->pos] == '\t')
			p->col += 1;
		else if (p->f_data[p->pos] == '\n')
		{
			p->col = 1;
			p->row += 1;
		}
		else
			break ;
		p->pos += 1;
	}
	if (p->f_data[p->pos] == '\0')
		asm_error(EOF, p->row, p->col);
}

void				asm_parser(char *path)
{
    t_asm_parser	*p;

    p = init_asm_parser(path);
	get_comment_name(p);

	ft_printf("%s\n%s\n", p->name, p->comment);




    ft_strdel(&(p->name));
    ft_strdel(&(p->comment));
    ft_vec_del(&(p->file));
    free(p);
}