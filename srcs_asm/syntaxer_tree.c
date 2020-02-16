#include "asm.h"

void 		collect_name(t_cursor *p)
{
	skip_nl(p);
	while (p->name == NULL || p->comment == NULL)
	{
		if (p->lex->next->type != STRING)
			token_error(p->lex->next);
		if (ft_strequ(p->lex->lex, NAME_CMD_STRING))
		{
			p->name = p->lex->next->lex;
			if (ft_strlen(p->name) > PROG_NAME_LENGTH)
				common_error(NAME_TOO_BIG);
		}
		else if (ft_strequ(p->lex->lex, COMMENT_CMD_STRING))
		{
			p->comment = p->lex->next->lex;
			if (ft_strlen(p->comment) > COMMENT_LENGTH)
				common_error(COMM_TOO_BIG);
		}
		p->lex = p->lex->next->next;
		if (p->lex->type != NL)
			token_error(p->lex);
		p->lex = p->lex->next;
	}
}

int32_t 			get_arg_size(t_lex *lx, uint8_t opcode, int a)
{
	if (lx->type == REGISTER)
	{
		if (op_tab[opcode - 1].args_types[a] & T_REG)
			return (sizeof(uint8_t));
	}
	else if (lx->type == INDIRECT || lx->type == INDIRECT_LABEL)
	{
		if (op_tab[opcode - 1].args_types[a] & T_IND)
			return (sizeof(uint16_t));
	}
	else if (lx->type == DIRECT || lx->type == DIRECT_LABEL)
	{
		if (op_tab[opcode - 1].args_types[a] & T_DIR)
			return (op_tab[opcode - 1].t_dir_size);
	}
	argument_error(lx, op_tab[opcode - 1].name);
	return (-1);
}

static void 	process_instruction(t_ins **root, t_cursor *p, t_lab **lab)
{
	int 		a = 0;

	add_ins(root, p->lex, *lab);
	*lab = NULL;
	p->lex = p->lex->next;
	while (p->lex->type != NL)
	{
		if (p->lex->type == DIRECT || p->lex->type == DIRECT_LABEL
			|| p->lex->type == INDIRECT || p->lex->type == INDIRECT_LABEL
			|| p->lex->type  == REGISTER)
		{
			(*root)->bytes += get_arg_size(p->lex, (*root)->code, a++);
			push_back_argument(&(*root)->args, p->lex);
		}
		else if (p->lex->type == SEPARATOR)
		{
			p->lex = p->lex->next;
			continue ;
		}
		else
			token_error(p->lex);
		p->lex = p->lex->next;
	}
}

void 			syntaxer(t_cursor *p)
{
	t_lab 		*lab;
	t_lex		*head;
	t_ins		*root;

	lab = NULL;
	root = NULL;
	head = p->lex;
	collect_name(p);
	while (p->lex->type != EOF)
	{
		while (p->lex->type == NL)
			p->lex = p->lex->next;
		if (p->lex->type == INSTRUCTION)
			process_instruction(&root, p, &lab);
		else if (p->lex->type == LABEL)
			add_label(&lab, p->lex);
		else
			token_error(p->lex);
		p->lex = p->lex->next;
	}
	p->lex = head;
	p->root = root;
}