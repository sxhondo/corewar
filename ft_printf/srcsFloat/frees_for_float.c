/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_for_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:07:44 by ylila             #+#    #+#             */
/*   Updated: 2019/12/10 22:07:47 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "high_precision.h"

void	clear_res_buff(t_result *res)
{
	free(res->buff);
	res->buff = NULL;
	res->bf_len = 0;
}

void	free_hp(t_high *hp)
{
	free(hp);
	hp = NULL;
}

void	free_l_hp(t_highl *hp)
{
	free(hp);
	hp = NULL;
}
