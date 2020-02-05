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
	t_ins			*instr;
	t_label			*lab;
    t_asm_parser	*p;

    instr = NULL;
    p = init_asm_parser(path);
	get_comment_name(p);
	while (skip_empty_space(p))
	{
		lab = label_parser(p);
		if (p->f_data[p->pos] == '\0')
			break ;
		ins_parser(p, lab, &instr);
	}
	print_collected(instr);
	free_all(p, instr);
}