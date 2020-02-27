/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_intf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:07:28 by ylila             #+#    #+#             */
/*   Updated: 2019/12/10 22:07:31 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "high_precision.h"

void		add_point(t_result *res, t_prsng *tools)
{
	if (tools->prec || tools->flags & M_PRECISION_NOT_ADDED ||
	tools->flags & M_SHARP)
	{
		ft_strncat(res->result, ".", 1);
		++res->len;
	}
}

char		*calculate_g_a_result(t_prsng *tools, t_mkfld *fld, int lg_10)
{
	char		*res;
	int			prec;

	res = NULL;
	if (ft_tolower(tools->type) == 'g')
	{
		if (!tools->prec && tools->flags & M_PRECISION_NOT_ADDED)
			tools->prec = 6;
		prec = (tools->prec) ? tools->prec : 1;
		if (!(res = get_g_result(tools, fld, lg_10)))
			return (NULL);
		if (tools->prec || tools->flags & M_PRECISION_NOT_ADDED ||
		tools->flags & M_SHARP)
			if (!(res = delete_lst_zeroes(res, fld, tools->type)))
				return (NULL);
		if (!(res = prepare_to_round(res, prec, fld, tools)))
			return (NULL);
	}
	return (res);
}
