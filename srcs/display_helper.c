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

#include "dasm.h"

void 			free_allocated(t_parser *p)
{
	t_op		*ptr;
	t_op 		*next;

	ptr = p->ops;
	while (ptr)
	{
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
	ft_strdel(&p->comment);
	ft_strdel(&p->name);
	free(p);
}

void 			display_collected(t_parser *p)
{
	int 	i;
	t_op 	*tmp;

	ft_printf("%s: {blue}%s{eoc}\n", p->name, p->comment);
	tmp = p->ops;
	while (tmp)
	{
		ft_printf("{red}%s{eoc}\n", op_tab[tmp->op - 1].name);
		i = 0;
		while (tmp->args_type_code[i] && i < 3)
		{
			if (tmp->args_type_code[i] == T_REG)
				ft_printf("T_REG \t");
			if (tmp->args_type_code[i] == T_DIR)
				ft_printf("T_DIR \t");
			if (tmp->args_type_code[i] == T_IND)
				ft_printf("T_IND \t");	
			i++;	
		}
		ft_printf("\n");
		i = 0;
		while (i < op_tab[tmp->op - 1].args_num)
		{
			ft_printf("%d\t", tmp->args[i]);
			i++;
		}
		ft_printf("\n---\n");
		tmp = tmp->next;
	}
}

void 			display_grid(uint8_t g[], unsigned size, int hl)
{
	int 		q;

	q = 0;
	while (q < size)
	{
		if ((q % 16) == 0)
			ft_printf("\n");
		if (hl == q)
			ft_printf("{red}%02x{eoc}", g[q]);
		else
			ft_printf("%02x", g[q]);
		if (q % 2)
			ft_printf("\t");
		q++;	
	}
	ft_printf("\n---\n");
}

void            display_error(int num)
{
    ft_printf("error: ");
    ft_printf("%s\n", errors[num]);
    exit (num);
}