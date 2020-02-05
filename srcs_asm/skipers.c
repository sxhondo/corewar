#include <asm.h>

int 				is_num(char c)
{
	return ((c >= '0' && c <= '9') || (c == '-' || c == '+'));
}

void 				skip_separator(t_asm_parser *p, t_ins *elem, int a)
{
	int 			args_amount;

	skip_tab_space(p);
	args_amount = op_tab[elem->code - 1].args_num;
	if (a == 0)
	{
		if (p->f_data[p->pos] != '%' && p->f_data[p->pos] != 'r' &&
			!is_num(p->f_data[p->pos]))
			asm_error(INVALID_SYNTAX, p->row, p->col);
	}
	else if (a < args_amount)
	{
		if (p->f_data[p->pos] && p->f_data[p->pos] != SEPARATOR_CHAR)
			asm_error(INVALID_SYNTAX, p->row, p->col);
		p->pos += 1;
		p->col += 1;
	}
	else if (a == args_amount - 1)
	{
		if (p->f_data[p->pos] && p->f_data[p->pos] != '\n')
			asm_error(INVALID_SYNTAX, p->row, p->col);
	}
	else if (a > args_amount)
		asm_error(INVALID_SYNTAX, p->row, p->col);
	skip_tab_space(p);
}

void 			skip_tab_space(t_asm_parser *p)
{
	while (p->f_data[p->pos] &&
		   (p->f_data[p->pos] == '\t' || p->f_data[p->pos] == ' '))
	{
		if (p->f_data[p->pos] == '\t')
			p->col += 4;
		else if (p->f_data[p->pos] == ' ')
			p->col += 1;
		p->pos += 1;
	}
	if (p->f_data[p->pos] == COMMENT_CHAR
		|| p->f_data[p->pos] == ALT_COMMENT_CHAR)
	{
		while (p->f_data[p->pos] && p->f_data[p->pos] != '\n')
		{
			ft_putchar(p->f_data[p->pos]);
			p->col += 1;
			p->pos += 1;
		}
		p->pos += 1;
	}
	if (p->pos == p->file->total - 1)
		asm_error(EOF, p->row, p->col);
}

int 				skip_empty_space(t_asm_parser *p)
{
	while (p->pos < p->file->total)
	{
		if (p->f_data[p->pos] == COMMENT_CHAR
			|| p->f_data[p->pos] == ALT_COMMENT_CHAR)
		{
			while (p->f_data[p->pos] && p->f_data[p->pos] != '\n')
				p->pos += 1;
		}
		if (p->f_data[p->pos] == ' ' || p->f_data[p->pos] == '\t')
			p->col += p->f_data[p->pos] == ' ' ? 1 : 4;
		else if (p->f_data[p->pos] == '\n')
		{
			p->col = 1;
			p->row += 1;
		}
		else
			break ;
		p->pos += 1;
	}
	if (p->f_data[p->pos] == '\0')
		return (0);
	return (1);
}
