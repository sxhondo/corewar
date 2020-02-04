#include "asm.h"

static void 		get_string(t_asm_parser *p, char **dst, char type)
{
	int 			i;

	p->col = 1;
	p->pos += type == 0 ? 4 : 7;
	p->col += type == 0 ? 4 : 7;
	if (*dst)
		asm_error(DUPL_NAME_COMMENT, p->row, p->col);
	skip_tab_space(p);
	if (p->f_data[p->pos++] == '"')
	{
		i = p->pos;
		while (p->f_data[i] && p->f_data[i] != '"')
			i++;
		if (p->f_data[i] == '\0')
			asm_error(EOF, p->row, p->col);
		if (i - p->pos > (type == 0 ? PROG_NAME_LENGTH : COMMENT_LENGTH))
			asm_error(BIG_NAME_COMMENT, p->row, p->col);
		if ((*dst = ft_strndup(p->f_data + p->pos, i - p->pos)) == NULL)
			asm_error(CANT_ALLOCATE, 0, 0);
		p->pos += i - p->pos + 1;
	}
	else
		asm_error(SYNTAX_ERROR, p->row, p->col);
}

void 				get_comment_name(t_asm_parser *p)
{
	unsigned		save;

	save = -1;
	skip_empty_space(p);
	if (p->f_data[p->pos])
	{
		while (p->name == NULL || p->comment == NULL)
		{
			skip_empty_space(p);
			if (save == p->row)
				asm_error(NO_NEW_LINE_NAME, p->row, p->col);
			if (p->f_data[p->pos++] != '.')
				asm_error(SYNTAX_ERROR, p->row, p->col);
			if (ft_strnequ(p->f_data + p->pos, "name", 4))
				get_string(p, &(p->name), 0);
			else if (ft_strnequ(p->f_data + p->pos, "comment", 7))
				get_string(p, &(p->comment), 1);
			save = p->row;
		}
	}
	else
		asm_error(EOF, p->col, p->row);
}

