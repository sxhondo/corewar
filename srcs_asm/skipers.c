#include <asm.h>

void 			skip_tab_space(t_asm_parser *p)
{
	while (p->f_data[p->pos] &&
		   (p->f_data[p->pos] == '\t' || p->f_data[p->pos] == ' '))
	{
		p->pos += 1;
		p->col += 1;
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
			p->col += 1;
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
		asm_error(EOF, p->row, p->col);
	return (1);
}
