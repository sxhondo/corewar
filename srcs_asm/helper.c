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

void 					print_tokens(t_lex *l)
{
	for (t_lex *tmp = l; tmp; tmp = tmp->next)
	{
		ft_printf("%d : %d \t", tmp->row, tmp->col);
		ft_printf("[%s] ", tokens[tmp->type]);
		ft_printf("%s\n", tmp->lex);
	}
}

void 					free_all(t_asm_parser *p, t_lex *lex)
{
	t_lex				*l;
	t_lex				*next;

	l = lex;
	while (l)
	{
		next = l->next;
		ft_strdel(&l->lex);
		free(l);
		l = next;
	}
	close(p->fd);
	ft_strdel(&(p->name));
	ft_strdel(&(p->comment));
	ft_vec_del(&(p->file));
	free(p);
}

//int						core_atoi(const char *str, int *num, t_asm_parser *p)
//{
//	int					sign;
//	long				res;
//	int					i;
//
//	i = 0;
//	res = 0;
//	sign = 1;
//	if ((*str == '-' || *str == '+') && ++i)
//		sign = *str++ == '-' ? -1 : 1;
//	if (!ft_isdigit(*str))
//		asm_error(INVALID_NUM, p->row, p->col);
//	while (*str && ft_isdigit(*str) && ++i)
//	{
//		if (!*str || *str < '0' || *str > '9')
//			asm_error(INVALID_NUM, p->row, p->col);
//		res = res * 10 + (*str++ - '0');
//		if ((sign == 1 && res > INT32_MAX)
//			|| (sign == -1 && res - 2 >= INT32_MAX))
//			asm_error(INVALID_NUM, p->row, p->col);
//	}
//	*num = (int)(res * sign);
//	return (i);
//}