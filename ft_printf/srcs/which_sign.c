/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_sign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:11:20 by mdeanne           #+#    #+#             */
/*   Updated: 2019/12/10 22:11:24 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

int		which_sign_aaeeffgg(t_un *number, t_prsng *tools)
{
	if ((tools->mdfirs == 0 && number->i < 0) ||
		(tools->mdfirs & M_L && number->l < 0) ||
		(tools->mdfirs & M_H && number->sh < 0) ||
		(tools->mdfirs & M_LL && number->ll < 0) ||
		(tools->mdfirs & M_HH && number->c < 0))
		return (-1);
	else if ((tools->mdfirs == 0 && number->i > 0) ||
			(tools->mdfirs & M_L && number->l > 0) ||
			(tools->mdfirs & M_H && number->sh > 0) ||
			(tools->mdfirs & M_LL && number->ll > 0) ||
			(tools->mdfirs & M_HH && number->c > 0))
		return (1);
	return (0);
}

int		which_sign(t_un *number, t_prsng *tools)
{
	if (!is_aaeeffgg(tools->type))
		return (which_sign_aaeeffgg(number, tools));
	else
	{
		if (((tools->mdfirs == 0 || tools->mdfirs & M_L)
			&& number->db < 0) ||
			(tools->mdfirs & M_UPPER_L && number->ldb < 0))
			return (-1);
		else if (((tools->mdfirs == 0 || tools->mdfirs & M_L)
					&& number->db > 0) ||
					(tools->mdfirs & M_UPPER_L && number->ldb > 0))
			return (1);
	}
	return (0);
}
