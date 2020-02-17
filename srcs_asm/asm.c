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

static int		check_ext(char *path)
{
	while (*path)
	{
		if (*path == '.' && ft_strequ(path, ".s"))
			return (1);
		path++;
	}
	return (0);
}

static void			asm_parser(char *path)
{
	t_cursor		*p;

	p = init_cursor(path);
	while (p->pos < p->file->total)
		lexer(p);
//	print_tokens(p->lex);
	syntaxer(p);
	analyzer(p);
	print_lexical_tree(p->root, 'f');
	free_all(p);
}


int				main(int ac, char **av)
{
	if (ac == 2 && check_ext(av[1]))
	{
		asm_parser(av[1]);
	}
	else
		common_error(BAD_ARGUMENT_FILE);
	return (0);
}