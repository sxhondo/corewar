/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:05:03 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/27 14:05:04 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char			*new_ext(char *path)
{
	int				i;
	char			*new;
	char			*str;

	i = 0;
	str = path;
	while (*str && !ft_strequ(str, ".s"))
	{
		str++;
		i++;
	}
	if (!(new = ft_strnew(i + 4)))
		common_error(CANT_ALLOCATE);
	ft_strncat(new, path, i);
	ft_strncat(new, ".cor", 4);
	return (new);
}

void				asm_parser(char *path)
{
	int				fd;
	char			*nxt;
	t_cursor		*p;

	p = init_cursor(path);
	while (p->pos < p->file->total)
		lexer(p);
	syntaxer(p);
	analyzer(p);
	p->code = write_code(p);
	nxt = new_ext(path);
	if ((fd = open(nxt, O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 0)
		common_error(CANT_CREATE);
	ft_printf("Writing output to %s\n", nxt);
	write(fd, p->code->data, p->code->total);
	close(fd);
	ft_strdel(&nxt);
	ft_vec_del(&p->code);
	free_all(p);
}
