/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 18:54:12 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 18:54:14 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "dasm.h"

static int		check_ext(char *path)
{
	while (*path)
	{
		if (*path == '.' && ft_strequ(path, ".s"))
			return (1);
		if (*path == '.' && ft_strequ(path, ".cor"))
			return (2);
		path++;
	}
	return (0);
}

int				main(int ac, char **av)
{
	if (check_ext(av[ac - 1]) == 1)
		asm_parser(av[ac - 1]);
	else if (check_ext(av[ac - 1]) == 2)
		dasm_parser(av[ac - 1]);
	else
		ft_printf("usage: ./asm <path_to_champion.s/cor>\n");
	return (0);
}
