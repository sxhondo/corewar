/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:47:22 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 19:47:22 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				collect_name(t_cursor *p)
{
	while (p->name == NULL || p->comment == NULL)
	{
		while (p->lex->type == NL)
			p->lex = p->lex->next;
		if (p->lex->type == EOF || p->lex->next->type != STRING)
			token_error(p->lex, p);
		if (ft_strequ(p->lex->lex, NAME_CMD_STRING) && !p->name)
		{
			if (p->lex->next)
				p->name = p->lex->next->lex;
			if (ft_strlen(p->name) > PROG_NAME_LENGTH)
				common_error(NAME_TOO_BIG);
		}
		else if (ft_strequ(p->lex->lex, COMMENT_CMD_STRING) && !p->comment)
		{
			p->comment = p->lex->next->lex;
			if (ft_strlen(p->comment) > COMMENT_LENGTH)
				common_error(COMM_TOO_BIG);
		}
		else
			token_error(p->lex, p);
		if ((p->lex = p->lex->next->next) && p->lex->type != NL)
			token_error(p->lex, p);
	}
}

int32_t				get_arg_size(t_lex *lx, uint8_t opcode, int a)
{
	if (lx->type == REGISTER)
	{
		if (g_op_tab[opcode - 1].args_types[a] & T_REG)
			return (sizeof(uint8_t));
	}
	else if (lx->type == INDIRECT || lx->type == INDIRECT_LABEL)
	{
		if (g_op_tab[opcode - 1].args_types[a] & T_IND)
			return (sizeof(uint16_t));
	}
	else if (lx->type == DIRECT || lx->type == DIRECT_LABEL)
	{
		if (g_op_tab[opcode - 1].args_types[a] & T_DIR)
			return (g_op_tab[opcode - 1].t_dir_size);
	}
	argument_error(lx, g_op_tab[opcode - 1].name);
	return (-1);
}

static void			process_instruction(t_ins **root, t_cursor *p)
{
	int				a;
	size_t			size;

	a = 0;
	p->lex = p->lex->next;
	while (p->lex->type != NL)
	{
		if (is_argument(p->lex->type))
		{
			size = get_arg_size(p->lex, (*root)->code, a);
			(*root)->bytes += size;
			push_back_argument(&(*root)->args, p->lex, size);
			p->lex = p->lex->next;
			a++;
			if ((is_separator(a, (*root)->code) && p->lex->type != SEPARATOR))
				token_error(p->lex, p);
			if ((!is_separator(a, (*root)->code) && p->lex->type == SEPARATOR))
				token_error(p->lex, p);
			if (p->lex->type == SEPARATOR)
				p->lex = p->lex->next;
		}
		else
			token_error(p->lex, p);
	}
}

void				syntaxer(t_cursor *p)
{
	t_lab			*lab;
	t_lex			*head;
	t_ins			*root;

	lab = NULL;
	root = NULL;
	head = p->lex;
	collect_name(p);
	while (skip_nl(p) && p->lex->type != EOF)
	{
		if (p->lex->type == INSTRUCTION)
		{
			add_ins(&root, p->lex, lab);
			lab = NULL;
			process_instruction(&root, p);
		}
		else if (p->lex->type == LABEL)
			add_label(&lab, p->lex->lex, p->row);
		else
			token_error(p->lex, p);
		p->lex = p->lex->next;
	}
	p->lab = lab;
	p->lex = head;
	p->root = root;
}
