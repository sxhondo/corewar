#include "asm.h"

static void 		get_string(t_asm_parser *p, char **dst, char *type)
{
	int 			i;

	p->pos += ft_strlen(type);
	p->col += ft_strlen(type);
	skip_tab_space(p);
	if (*dst)
		asm_error(DUPL_NAME_COMMENT, p->row, p->col);
	if (p->f_data[p->pos++] != '"')
		asm_error(INVALID_SYNTAX, p->row, p->col);
	i = 0;
	while (p->f_data[p->pos + i] && p->f_data[p->pos + i] != '"')
		i++;
	if (p->f_data[p->pos + i] == '\0')
		asm_error(EOF, p->row, p->col);
	if (i > (type[0] == 'n' ? PROG_NAME_LENGTH : COMMENT_LENGTH))
		asm_error(STR_TOO_BIG, p->row, p->col);
	if ((*dst = ft_strndup(p->f_data + p->pos, i)) == NULL)
		asm_error(CANT_ALLOCATE, 0, 0);
	p->col += i + 2;
	p->pos += i + 1;
}

void 				get_comment_name(t_asm_parser *p)
{
	skip_empty_space(p);
	if (p->f_data[p->pos])
	{
		while (p->name == NULL || p->comment == NULL)
		{
			skip_empty_space(p);
			if (ft_strnequ(p->f_data + p->pos, NAME_CMD_STRING, 4))
				get_string(p, &(p->name), NAME_CMD_STRING);
			else if (ft_strnequ(p->f_data + p->pos, COMMENT_CMD_STRING, 7))
				get_string(p, &(p->comment), COMMENT_CMD_STRING);
			else
				asm_error(INVALID_SYNTAX, p->row, p->col);
		}
	}
	else
		asm_error(EOF, p->col, p->row);
}

