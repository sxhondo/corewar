#include "asm.h"

int 			is_num(char c)
{
	return ((c >= '0' && c <= '9') || c == '-');
}

int 			is_lowcase_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}

void 				cursor_right_shift(t_asm_parser *p)
{
	while (p->f_data[p->pos] && p->f_data[p->pos] != '\n' &&
		(p->f_data[p->pos] == ' '  || p->f_data[p->pos] == '\t'))
	{
		if ((p->f_data[p->pos] == COMMENT_CHAR
			 || p->f_data[p->pos] == ALT_COMMENT_CHAR))
		{
			while (p->f_data[p->pos] && p->f_data[p->pos] != '\n' && ++p->col)
				p->pos += 1;
		}
		p->col += 1;
		p->pos += 1;
	}
}