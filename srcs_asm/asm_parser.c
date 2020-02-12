/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:46:09 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/27 14:46:10 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_lex 		*validate_name(t_asm_parser *p, t_lex *lx)
{
	if ((lx = skip_nl(lx)) && lx->type != COMMAND)
		token_error(lx);
	while (p->name == NULL || p->comment == NULL)
	{
		if (lx->next->type != STRING)
			token_error(lx->next);
		if (ft_strequ(lx->lex, NAME_CMD_STRING))
		{
			p->name = lx->next->lex;
			if (ft_strlen(p->name) > PROG_NAME_LENGTH)
				common_error(NAME_TOO_BIG);
		}
		else if (ft_strequ(lx->lex, COMMENT_CMD_STRING))
		{
			p->comment = lx->next->lex;
			if (ft_strlen(p->comment) > COMMENT_LENGTH)
				common_error(COMM_TOO_BIG);
		}
		lx = lx->next->next;
		if (lx->type != NL)
			token_error(lx);
		lx = lx->next;
	}
	return (lx);
}

static void 		handle_expressions(t_asm_parser *p, t_lex *lx)
{
	lx = validate_name(p, lx);
	while ((lx = skip_nl(lx)) && lx->type != EOF)
	{
		if (lx->type == LABEL)
		{
			push_label(p, lx);
			lx = lx->next;
		}
		else if (lx->type == INSTRUCTION)
			lx = handle_operations(p, lx);
		else
			token_error(lx);
	}
	check_unused_refs(p, p->ref, p->lab);
}

void				asm_parser(char *path)
{
	t_asm_parser	*p;

    p = init_asm_parser(path);
	while (p->pos < p->file->total - 1 && skip_void(p))
		parse_expressions(p);
	push_lexeme(p, EOF, NULL);
	p->pos = 0;
	handle_expressions(p, p->lex);

//	print_tokens(p->lex);
	free_all(p);
}