/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:17:31 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/16 18:56:47 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		delete_elem(t_processes **processes, t_info *info)
{
	t_processes		*copy;

	copy = (*processes);
	if ((*processes)->prev)
	{
		((*processes)->prev)->next = (*processes)->next;
		if ((*processes)->next)
			((*processes)->next)->prev = (*processes)->prev;
	}
	else if ((*processes)->next)
	{
		((*processes)->next)->prev = NULL;
		info->processes = (*processes)->next;
	}
	else
		info->processes = NULL;
	(*processes) = (*processes)->next;
	free(copy);
	copy = NULL;
}

void		add_elem(t_processes **processes, int index, int number_player)
{
	t_processes	*new;

	if (!(new = (t_processes *)malloc(sizeof(t_processes))))
		error(8);
	new->next = NULL;
	new->prev = NULL;
	new->carry = 0;
	new->cc_op = 0;
	new->cc_live = 0;
	new->code_op = 0;
	new->index = index % MEM_SIZE;
	ft_bzero(new->reg, sizeof(int) * REG_NUMBER);
	(new->reg)[0] = -number_player;
	if (*processes == NULL)
		*processes = new;
	else
	{
		new->next = *processes;
		(*processes)->prev = new;
		*processes = new;
	}
}

void		create_processes(t_info *info)
{
	int		i;
	int		shift;

	i = 0;
	while (++i <= info->count_process)
	{
		shift = (MEM_SIZE / info->count_process) * (i - 1);
		add_elem(&(info->processes), shift, i);
	}
}
