#include "asm.h"

int 				is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v');
}

int 				is_num(char c)
{
	return (ft_isdigit(c) || c == '-');
}

int 				get_operator(char *name)
{
	int  			i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(name, op_tab[i].name))
			return (op_tab[i].code);
		i++;
	}
	return (0);
}

int 				is_label_char(char c)
{
	int 			i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (LABEL_CHARS[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int 				skip_void(t_asm_parser *p)
{
	while (p->f_data[p->pos] && (is_whitespace(p->f_data[p->pos])))
	{
		p->col += p->f_data[p->pos] == '\t' ? 4 : 1;
		p->pos += 1;
	}
	if (p->f_data[p->pos] == COMMENT_CHAR || p->f_data[p->pos] == ALT_COMMENT_CHAR)
	{
		while (p->f_data[p->pos] && p->f_data[p->pos] != '\n')
		{
			p->pos += 1;
			p->col += 1;
		}
	}
	return (1);
}