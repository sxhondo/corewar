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

static t_lex 		*skip_nl(t_lex *lx)
{
	while (lx->type == NL)
		lx = lx->next;
	return (lx);
}

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

static void 		validate_labels(t_asm_parser *p, t_lex *lx)
{
	push_label(p, lx);
}

static void 		validate_direct(t_asm_parser *p, t_lex *lx, t_op_tab op, int a)
{
	t_int32			k;

	if (op.args_types[a] == T_DIR)
	{
		//LABEL
		k.num = core_atoi(lx->lex, lx);
//		vec_write(p, op.t_dir_size, k);
	}
	else
		argument_error(lx, op.name);
}

static void 		validate_indirect(t_asm_parser *p, t_lex *lx, t_op_tab op, int a)
{
	t_int32			k;

	if (op.args_types[a] & T_IND)
	{
		//LABEL
		k.num = core_atoi(lx->lex, lx);
//		vec_write(p, op.t_dir_size, k);
	}
	else
		argument_error(lx, op.name);
}

static t_lex 		*validate_arguments(t_asm_parser *p, t_lex *lx, t_op_tab op)
{
	int 			i;

	i = 0;
	while (i < op.args_num)
	{
		if (lx->type == DIRECT || lx->type == DIRECT_LABEL)
			validate_direct(p, lx, op, i);
		if (lx->type == INDIRECT || lx->type == INDIRECT_LABEL)
			validate_indirect(p, lx, op, i);
		lx = lx->next;
		i++;
	}
	return (lx);
}

static void 		validate_instruction(t_asm_parser *p, t_lex *lx)
{
	t_op_tab		op;
	t_int32			o;

	while (lx->type != NL && lx->type != EOF)
	{
		o.num = get_operator(lx->lex);
		int32_converter(p, sizeof(uint8_t), o);
		op = op_tab[o.num - 1];
		if (op.args_type_code)
			args_type_converter(lx->next, op, p);
		lx = validate_arguments(p, lx->next, op);
	}
}

static void 		validate_expressions(t_asm_parser *p, t_lex *lx)
{
	lx = validate_name(p, lx);
	while (lx->type != EOF)
	{
		lx = skip_nl(lx);
		if (lx->type == INSTRUCTION)
			validate_instruction(p, lx);

		break ;
	}

}

void				asm_parser(char *path)
{
	t_asm_parser	*p;

    p = init_asm_parser(path);
	while (p->pos < p->file->total - 1 && skip_void(p))
		parse_expressions(p);
	p->pos = -1;
	push_lexeme(p, EOF, NULL);
	validate_expressions(p, p->lex);
//	print_labels(p->lab);
	print_tokens(p->lex);
	free_all(p);
}