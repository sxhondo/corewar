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

static void 		parse_label_instruction(t_asm_parser *p, t_lex **lx)
{
	char 			*str;
	int 			i;

	i = 0;
	while (p->f_data[p->pos + i] &&
				is_lowcase_alpha(p->f_data[p->pos + i]) && ++p->col)
		i++;
	if (p->f_data[p->pos + i] == LABEL_CHAR)
	{
		if (!(str = ft_strndup(p->f_data + p->pos, i)))
			common_error(CANT_ALLOCATE);
		push_lexeme(lx, LABEL, str, p);
	}
	else if (p->f_data[p->pos + i])
	{
		if (!(str = ft_strndup(p->f_data + p->pos, i)))
			common_error(CANT_ALLOCATE);
		push_lexeme(lx, INSTRUCTION, str, p);
	}
	p->pos += i + 1;
}

static void 		parse_comment_name(t_asm_parser *p, t_lex **lx, char *type)
{
	char 			*tmp;
	int 			i;

	i = 0;
	p->col += ft_strlen(type);
	p->pos += ft_strlen(type);
	cursor_right_shift(p);
	if (p->f_data[p->pos++] != '"')
		lexical_error(p->row, p->col);
	while (p->f_data[p->pos + i] && p->f_data[p->pos + i] != '"')
	{
		if (p->f_data[p->pos + i] == '\n')
		{
			p->col = 1;
			p->row += 1;
		}
//		p->col += 1;
		i++;
	}
//	p->col += 1;
	if (i > ((type[1] == 'n') ? PROG_NAME_LENGTH : COMMENT_LENGTH))
		common_error(STR_TOO_BIG);
	if ((tmp = ft_strndup(p->f_data + p->pos, i)) == NULL)
		common_error(CANT_ALLOCATE);
	p->pos += i + 1;
	push_lexeme(lx, type[1] == 'n' ? NAME : COMMENT, tmp, p);
}

static void 		parse_argument(t_asm_parser *p, t_lex **lx)
{
	char 			*tmp;
	int 			type;
	int 			i;

	type = 0;
	if (p->f_data[p->pos] == 'r' && ++p->pos)
		type = REGISTER;
	else if (p->f_data[p->pos] == '%' && ++p->pos)
	{
		type = DIRECT;
		if (p->f_data[p->pos] == ':' && ++p->pos)
		{
			i = 0;
			while (p->f_data[p->pos + i]
				&& is_lowcase_alpha(p->f_data[p->pos + i]))
				i++;
			if (!(tmp = ft_strndup(p->f_data + p->pos, i)))
				common_error(CANT_ALLOCATE);
			push_lexeme(lx, type, tmp, p);
			p->pos += i;
			return ;
		}
	}
	else if (is_num(p->f_data[p->pos]))
		type = INDIRECT;
	i = 0;
	while (ft_isdigit(p->f_data[p->pos + i]) && is_num(p->f_data[p->pos + i]))
		i++;
	if (!(tmp = ft_strndup(p->f_data + p->pos, i)))
		common_error(CANT_ALLOCATE);
	p->pos += i;
	push_lexeme(lx, type, tmp, p);
}

static void 		parse_expressions(t_asm_parser *p, t_lex **lx)
{
	if (p->f_data[p->pos] == '.')
	{
		if (ft_strnequ(p->f_data + p->pos, NAME_CMD_STRING, 4))
			parse_comment_name(p, lx, NAME_CMD_STRING);
		else if (ft_strnequ(p->f_data + p->pos, COMMENT_CMD_STRING, 8))
			parse_comment_name(p, lx, COMMENT_CMD_STRING);
		else
			lexical_error(p->row, p->col);
	}
	else if (p->f_data[p->pos] == '\n' && ++p->pos && ++p->row)
	{
		push_lexeme(lx, NL, NULL, p);
		p->col = 0;
	}
	else if (is_lowcase_alpha(p->f_data[p->pos]))
		parse_label_instruction(p, lx);
	else if (is_num(p->f_data[p->pos]) ||
			p->f_data[p->pos] == '%' || p->f_data[p->pos == 'r'])
		parse_argument(p, lx);
	else
		lexical_error(p->row, p->col);
}

void				asm_parser(char *path)
{
	t_asm_parser	*p;
	t_lex			*lx;

	lx = NULL;
    p = init_asm_parser(path);
	while (p->pos < p->file->total - 1 && ++p->col)
	{
		cursor_right_shift(p);
		if (p->f_data[p->pos])
			parse_expressions(p, &lx);
	}
	print_tokens(lx);
	free_all(p, lx);

}