/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 18:59:17 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 18:59:18 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

static void				check_header(int fd)
{
	uint8_t				b[4];

	if ((read(fd, &b, 4)) != 4)
		d_error(INVALID_FILE);
	if (b[0] == 0u &&
		b[1] == ((COREWAR_EXEC_MAGIC) >> 16u) &&
		b[2] == (uint8_t)(COREWAR_EXEC_MAGIC >> 8u) &&
		b[3] == (uint8_t)(COREWAR_EXEC_MAGIC))
		return ;
	else
		d_error(INVALID_HEADER);
}

static char				*check_string(int fd, int type)
{
	int					i;
	int					k;
	char				*res;
	uint8_t				b[type];

	if ((read(fd, &b, type) != type))
		d_error(INVALID_FILE);
	k = 0;
	i = 0;
	while (i < type)
	{
		if (b[i] != 0)
			k++;
		i++;
	}
	if ((res = ft_strnew(k)) == NULL)
		d_error(CANT_ALLOCATE);
	ft_strncat(res, (char *)b, k);
	return (res);
}

static void				check_null(int fd)
{
	uint8_t				b[4];

	if ((read(fd, &b, 4) != 4))
		d_error(INVALID_FILE);
	if (b[0] || b[1] || b[2] || b[3])
		d_error(INVALID_NULL);
}

static unsigned			check_exec_size(int fd)
{
	union u_int32		tmp;
	uint8_t				b[4];

	if ((read(fd, &b, 4) != 4))
		d_error(INVALID_FILE);
	tmp.octets.o1 = b[3];
	tmp.octets.o2 = b[2];
	tmp.octets.o3 = b[1];
	tmp.octets.o4 = b[0];
	return (tmp.num);
}

void					dasm_parser(char *path)
{
	t_parser			*p;

	p = init_parser(path);
	check_header(p->fd);
	p->name = check_string(p->fd, PROG_NAME_LENGTH);
	check_null(p->fd);
	p->exe_code_size = check_exec_size(p->fd);
	p->comment = check_string(p->fd, COMMENT_LENGTH);
	check_null(p->fd);
	check_exec_code(p);
	write_to_file(p, path);
	free_allocated(p);
}
