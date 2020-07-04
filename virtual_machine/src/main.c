/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:34:54 by rgyles            #+#    #+#             */
/*   Updated: 2020/02/09 14:36:30 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

void		init_info(t_info *info)
{
	int		i;

	if (!(info->arena = (unsigned char *)malloc(MEM_SIZE)))
		error(8);
	ft_bzero(info->arena, MEM_SIZE);
	info->dump = -1;
	info->cycle_to_die = CYCLE_TO_DIE;
	info->count_cycles = 0;
	info->count_live = 0;
	info->count_check = 0;
	info->i = 0;
	info->processes = NULL;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		(info->players)[i].magic = 0;
		(info->players)[i].prog_size = 0;
		ft_bzero((info->players)[i].prog_name, PROG_NAME_LENGTH + 1);
		ft_bzero((info->players)[i].comment, COMMENT_LENGTH + 1);
	}
}

static void	print_winner(t_info *info)
{
	char	announcement[200];

	ft_strcpy(announcement, "Contestant ");
	ft_strcat(announcement, ft_itoa(info->last_live));
	ft_strcat(announcement, ", \"");
	ft_strcat(announcement, info->players[info->last_live - 1].prog_name);
	ft_strcat(announcement, "\", has won !\n");
	ft_putstr(announcement);
}

static void	visualization(t_info *info, t_sdl *sdl)
{
	if (init_sdl(info->arena, sdl))
		error(8);
	initialize_visual_arena(sdl, info);
	event_handler(info, sdl);
	free_resources(sdl);
}

static void	dumping(t_info *info)
{
	int		play;

	play = 0;
	present_champion(info->players);
	while (info->count_cycles < info->dump && play != -1)
		gladiatorial_fight(&play, info, NULL);
	if (play != -1)
		print_arena(info->arena);
	else
		print_winner(info);
}

int			main(int argc, char *argv[])
{
	t_info	info;
	t_sdl	sdl;
	int		play;

	if (argc == 1)
		usage();
	if (argc < 2)
		error(7);
	init_info(&info);
	read_arg(&info, argc, argv);
	create_processes(&info);
	if (info.dump == -666)
		visualization(&info, &sdl);
	else if (info.dump >= 0)
		dumping(&info);
	else
	{
		play = 0;
		present_champion(info.players);
		while (play != -1)
			gladiatorial_fight(&play, &info, NULL);
		print_winner(&info);
	}
	return (0);
}
