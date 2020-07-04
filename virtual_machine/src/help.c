/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:51:50 by bdudley           #+#    #+#             */
/*   Updated: 2020/02/01 21:33:07 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			error_1(int err)
{
	if (err == 6)
		perror("File exceeds maximum size for champion\n");
	else if (err == 7)
		perror("No champions are found\n");
	else if (err == 8)
		perror("Memory allocation error\n");
	else if (err == 9)
		perror("Found extra data\n");
	else if (err == 10)
		perror("Actual program size does not equal to declared size\n");
	else if (err == 11)
		perror("File exceeds minimum size for champion\n");
}

void				error(int err)
{
	if (err == 0)
		perror("File did not open\n");
	else if (err == 1)
		perror("Invalid argument after n - number is less \
than 1 or greater than the number of champions\n");
	else if (err == 2)
		perror("Invalid champion - no .cor extension found\n");
	else if (err == 3)
		perror("Champion with this ID already exists\n");
	else if (err == 4)
		perror("Reading error - not enough data\n");
	else if (err == 5)
		perror("Not a binary file\n");
	else
		error_1(err);
	exit(1);
}

unsigned int		get_magic(int fd)
{
	unsigned int	magic;
	unsigned int	buf;

	buf = 0;
	magic = 0;
	if (read(fd, &buf, 4) == -1)
		error(4);
	magic += ((buf & 0xff) << (8 * 3));
	magic += ((buf & 0xff00) << (8 * 1));
	magic += ((buf & 0xff0000) >> (8 * 1));
	magic += ((buf & 0xff000000) >> (8 * 3));
	if (magic != COREWAR_EXEC_MAGIC)
		error(5);
	return (magic);
}

void				shift_next_op(unsigned char code_arg,
		short int num_fun, t_processes **prs, t_sdl *sdl)
{
	int				skiped_bytes;
	short int		current_location;

	current_location = (*prs)->index;
	skiped_bytes = get_bytes_to_skip(num_fun, code_arg);
	if (sdl != NULL)
		move_cursor(current_location, skiped_bytes, -(*prs)->reg[0] - 1, sdl);
	(*prs)->index = (current_location + skiped_bytes) % MEM_SIZE;
}

void				present_champion(t_header *players)
{
	int		i;
	char	announcement[3000];

	i = -1;
	ft_putstr("Introducing contestants...\n");
	while (++i < MAX_PLAYERS && players[i].magic == COREWAR_EXEC_MAGIC)
	{
		ft_strcpy(announcement, "* Player ");
		ft_strcat(announcement, ft_itoa(i + 1));
		ft_strcat(announcement, ", weighing ");
		ft_strcat(announcement, ft_itoa(players[i].prog_size));
		ft_strcat(announcement, " bytes, ");
		ft_strcat(announcement, "\"");
		ft_strcat(announcement, players[i].prog_name);
		ft_strcat(announcement, "\" (\"");
		ft_strcat(announcement, players[i].comment);
		ft_strcat(announcement, "\") !\n");
		ft_putstr(announcement);
	}
}
