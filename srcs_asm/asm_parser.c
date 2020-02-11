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

static int32_t 			validate_indirect(t_asm_parser *p, t_lex *lx, t_op_tab op, int i)
{
	if (op.args_types[i] & T_IND)
	{
		return (core_atoi(lx->lex, lx));
	}
	else
		argument_error(lx, op.name);
}

static int32_t			validate_register(t_asm_parser *p, t_lex *lx, t_op_tab op, int i)
{
	if (op.args_types[i] & T_REG)
	{
		return (core_atoi(lx->lex, lx));
	}
	else
		argument_error(lx, op.name);
}

static int32_t 			validate_direct(t_asm_parser *p, t_lex *lx, t_op_tab op, int i)
{
	int32_t 			tmp;

	if (op.args_types[i] & T_DIR)
	{
		if (lx->type == DIRECT)
			return (core_atoi(lx->lex, lx));
		else if (lx->type == DIRECT_LABEL)
		{
			if ((tmp = find_label_diff(p->lab, lx->lex, p->pos)) != -1)
				return (tmp);
			push_ref(p, op.t_dir_size, lx->lex);
			return (-1);
		}
	}
	else
		argument_error(lx, op.name);
}

static t_lex 			*validate_arguments(t_asm_parser *p, t_lex *lx, t_op_tab op)
{
	uint8_t 			a_types[3];
	int32_t 			args[3];
	int 				i;

	i = -1;
	while (++i < op.args_num)
	{
		if (lx->type == DIRECT || lx->type == DIRECT_LABEL)
		{
			a_types[i] = T_DIR;
			args[i] = validate_direct(p, lx, op, i);
		}
		else if (lx->type == INDIRECT || lx->type == INDIRECT_LABEL)
		{
			a_types[i] = T_IND;
			args[i] = validate_indirect(p, lx, op, i);
		}
		else if (lx->type == REGISTER)
		{
			a_types[i] = T_REG;
			args[i] = validate_register(p, lx, op, i);
		}
		lx = lx->next;
		if (i < op.args_num - 1)
			lx->type == SEPARATOR ? lx = lx->next : token_error(lx);
	}
	write_arguments(a_types, args, p, op);
	return (lx);
}

static t_lex 		*validate_instruction(t_asm_parser *p, t_lex *lx)
{
	t_op_tab		op;
	t_int32			k;

	k.num = get_operator(lx->lex);
	int32_converter(p, sizeof(uint8_t), k, 0);
	p->pos += sizeof(uint8_t);
	op = op_tab[k.num - 1];

	/* *** */
//	ft_printf("operation: %08b\n", ((uint8_t *)p->code->data)[p->pos]);
//	display_grid(p->code->data, p->code->total, p->pos);
	/* *** */

	if ((lx = validate_arguments(p, lx->next, op))->type != NL)
		token_error(lx);
	return (lx);
}

static t_lex 		*validate_labels(t_asm_parser *p, t_lex *lx)
{
	while (p->ref)
	{
		if (ft_strequ(p->ref->name, lx->lex))
		{
			restore_ref(p, p->ref);
		}
		p->ref = p->ref->next;
	}
	push_label(p, lx);
	return (lx->next);
}


static void 		validate_expressions(t_asm_parser *p, t_lex *lx)
{
	lx = validate_name(p, lx);
	while (lx->type != EOF)
	{
		lx = skip_nl(lx);
		if (lx->type == LABEL)
			lx = validate_labels(p, lx);
		else if (lx->type == INSTRUCTION)
			lx = validate_instruction(p, lx);
	}
}

void				asm_parser(char *path)
{
	t_asm_parser	*p;

    p = init_asm_parser(path);
	while (p->pos < p->file->total - 1 && skip_void(p))
		parse_expressions(p);
	push_lexeme(p, EOF, NULL);
	p->pos = 0;
	validate_expressions(p, p->lex);
	print_labels(p->lab);
	print_tokens(p->lex);
	free_all(p);
}