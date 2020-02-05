#include "asm.h"

int 				is_label_char(char ch)
{
	int 			i;
	int 			len;

	i = 0;
	len = ft_strlen(LABEL_CHARS);
	while (i < len)
	{
		if (LABEL_CHARS[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

t_label 			*label_parser(t_asm_parser *p)
{
	t_label			*dst;
	int 			i;

	dst = NULL;
	while (skip_empty_space(p))
	{
		i = 0;
		while (p->f_data[p->pos + i] && is_label_char(p->f_data[p->pos + i]))
			i++;
		if (p->f_data[p->pos + i] == '\0')
			asm_error(EOF, p->row, p->col + i);
		else if (p->f_data[p->pos + i] == LABEL_CHAR)
			add_label(&dst, init_label(p->f_data + p->pos, i, p));
		else
			break ;
		p->pos += i + 1;
		p->col += i + 1;
		skip_tab_space(p);
		if (p->f_data[p->pos] != '\n')
			asm_error(INVALID_SYNTAX, p->row, p->col);
	}
	return (dst);
}
