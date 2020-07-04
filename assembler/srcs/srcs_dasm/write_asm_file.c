/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_asm_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:32:27 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 19:32:27 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

static char		*update_path(char *path)
{
	int			len;
	char		*str;

	len = ft_strlen(path);
	if ((str = ft_strnew(len - 2)) == NULL)
		d_error(CANT_ALLOCATE);
	ft_strncat(str, path, len - 3);
	ft_strcat(str, "s");
	return (str);
}

static void		write_operations(t_op *op, int fd)
{
	int			i;

	while (op)
	{
		ft_fprintf(fd, "%s ", g_op_tab[op->op - 1].name);
		if (g_op_tab[op->op - 1].args_type_code == 0)
			ft_fprintf(fd, "%c%d", DIRECT_CHAR, op->args[0]);
		else
		{
			i = -1;
			while (++i < g_op_tab[op->op - 1].args_num)
			{
				if (op->args_type_code[i] == DIR_CODE)
					ft_fprintf(fd, "%c%d", DIRECT_CHAR, op->args[i]);
				if (op->args_type_code[i] == REG_CODE)
					ft_fprintf(fd, "%c%d", 'r', op->args[i]);
				if (op->args_type_code[i] == IND_CODE)
					ft_fprintf(fd, "%d", op->args[i]);
				if (i + 1 < g_op_tab[op->op - 1].args_num)
					ft_fprintf(fd, ", ");
			}
		}
		ft_fprintf(fd, "\n");
		op = op->next;
	}
}

void			write_to_file(t_parser *p, char *path)
{
	int			fd;
	char		*up;

	up = update_path(path);
	if ((fd = open(up, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO)) < 0)
		d_error(CANT_CREATE);
	ft_printf("Writing output to %s\n", up);
	ft_fprintf(fd, ".name \"%s\"\n", p->name);
	ft_fprintf(fd, ".comment \"%s\"\n\n", p->comment);
	write_operations(p->ops, fd);
	close(fd);
	ft_strdel(&up);
}
