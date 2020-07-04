/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:27:43 by bdudley           #+#    #+#             */
/*   Updated: 2020/02/01 21:31:18 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "corewar.h"

static unsigned int	get_prog_size(int fd)
{
	unsigned int	prog_size;
	unsigned int	buf;

	buf = 0;
	prog_size = 0;
	if (read(fd, &buf, 4) == -1)
		error(4);
	prog_size += ((buf & 0xff) << (8 * 3));
	prog_size += ((buf & 0xff00) << (8 * 1));
	prog_size += ((buf & 0xff0000) >> (8 * 1));
	prog_size += ((buf & 0xff000000) >> (8 * 3));
	if (prog_size > CHAMP_MAX_SIZE)
		error(6);
	if (prog_size == 0)
		error(11);
	return (prog_size);
}

static void			read_arena(t_info *info, int fd, int number, int count)
{
	unsigned int	shift;
	int				len;
	char			c;

	shift = (MEM_SIZE / count) * number;
	len = read(fd, info->arena + shift, (info->players)[number].prog_size);
	if (len == -1)
		error(4);
	else if (len < (int)(info->players)[number].prog_size)
		error(10);
	len = read(fd, &c, 1);
	if (len != 0)
		error(9);
}

static void			read_file(t_info *info, char *file_name,
					int number, int count)
{
	int	fd;
	int	num;

	num = 0;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		error(0);
	if (number >= 0 && (info->players)[number].magic == COREWAR_EXEC_MAGIC)
		error(3);
	if (number < 0)
	{
		number = 0;
		while ((info->players)[number].magic == COREWAR_EXEC_MAGIC)
			++number;
	}
	(info->players)[number].magic = get_magic(fd);
	if (read(fd, (info->players)[number].prog_name, PROG_NAME_LENGTH) == -1)
		error(4);
	if ((read(fd, &num, 4) == -1) || (num != 0))
		error(4);
	(info->players)[number].prog_size = get_prog_size(fd);
	if (read(fd, (info->players)[number].comment, COMMENT_LENGTH) == -1
									|| read(fd, &num, 4) == -1 || num != 0)
		error(4);
	read_arena(info, fd, number, count);
	close(fd);
}

static int			count_champion(t_info *info, int argc, char *argv[])
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], DUMP) && i + 1 < argc)
			++i;
		else if (!ft_strcmp(argv[i], N) && i + 2 < argc
		&& ft_strrchr(argv[i + 2], '.')
		&& !ft_strcmp(COR, ft_strrchr(argv[i + 2], '.')))
		{
			i += 2;
			count++;
		}
		else if (ft_strrchr(argv[i], '.') &&
		!ft_strcmp(COR, ft_strrchr(argv[i], '.')))
			count++;
		else
			error(2);
	}
	info->last_live = count;
	info->count_process = count;
	return (count);
}

void				read_arg(t_info *info, int argc, char *argv[])
{
	int				i;
	int				number;
	int				count;

	i = 0;
	count = count_champion(info, argc, argv);
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], DUMP) && i + 1 < argc)
			info->dump = ft_atoi(argv[++i]);
		else if (!ft_strcmp(argv[i], N) && i + 2 < argc)
		{
			if ((number = ft_atoi(argv[++i])) < 1 || number > count)
				error(1);
			read_file(info, argv[++i], number - 1, count);
		}
	}
	i = 0;
	while (++i < argc)
		if (!ft_strcmp(argv[i], DUMP) && i + 1 < argc)
			++i;
		else if (!ft_strcmp(argv[i], N) && i + 2 < argc)
			i += 2;
		else
			read_file(info, argv[i], -1, count);
}
