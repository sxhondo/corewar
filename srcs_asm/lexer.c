#include "asm.h"

static void 		get_string(t_asm_parser *p)
{
	char 			*new;
	int 			i;

	i = 0;
	while (p->f_data[p->pos + i] != '"')
	{
		if (p->f_data[p->pos + i] == '\n' && ++p->row)
			p->col = 1;
		i++;
	}
	if (!(new = ft_strndup(p->f_data + p->pos, i)))
		common_error(CANT_ALLOCATE);
	push_lexeme(p, STRING, new);
	p->pos += i + 1;
	p->col += i + 1;
}

static void 		get_command(t_asm_parser *p)
{
	char 			*tmp;
	int 			i;

	i = 0;
	while (p->f_data[p->pos + i] &&
		   (ft_isalpha(p->f_data[p->pos + i]) || p->f_data[p->pos + i] == '.'))
		i++;
	if (!(tmp = ft_strndup(p->f_data + p->pos, i)))
		common_error(CANT_ALLOCATE);
	push_lexeme(p, COMMAND, tmp);
	p->col += i;
	p->pos += i;
}

static char 		*get_direct(t_asm_parser *p)
{
	int 			i;
	char 			*tmp;
	int 			type;

	i = 0;
	type = 0;
	if (p->f_data[p->pos] == LABEL_CHAR && p->pos++ && p->col++)
	{
		while (p->f_data[p->pos + i] && is_label_char(p->f_data[p->pos + i]))
			i++;
		type = DIRECT_LABEL;
	}
	else if (is_num(p->f_data[p->pos]))
	{
		while (p->f_data[p->pos + i] && is_num(p->f_data[p->pos + i]))
			i++;
		type = DIRECT;
	}
	if (!(tmp = ft_strndup(p->f_data + p->pos, i)))
		common_error(CANT_ALLOCATE);
	push_lexeme(p, type, tmp);
	p->pos += i;
	p->col += i;
	return (tmp);
}

static void 	get_lirii(t_asm_parser *p)
{
	char 		*tmp;
	int 		len;
	int 		i;

	i = 0;
	while (p->f_data[p->pos + i] && (p->f_data[p->pos + i] == LABEL_CHAR ||
	is_label_char(p->f_data[p->pos + i]) || is_num(p->f_data[p->pos + i])))
		i++;
	if ((tmp = ft_strndup(p->f_data + p->pos, i)) == NULL)
		common_error(CANT_ALLOCATE);
	len = ft_strlen(tmp);
	if (tmp[len - 1] == LABEL_CHAR)
		push_lexeme(p, LABEL, ft_realloc(tmp, len - 1));
	else if (tmp[0] == LABEL_CHAR)
		push_lexeme(p, INDIRECT_LABEL, ft_realloc(tmp + 1, len - 1));
	else if (tmp[0] == 'r')
		push_lexeme(p, REGISTER, ft_realloc(tmp + 1, len - 1));
	else if (get_operator(tmp))
		push_lexeme(p, INSTRUCTION, ft_realloc(tmp, len));
	else
		push_lexeme(p, INDIRECT, ft_realloc(tmp, len));
	ft_strdel(&tmp);
	p->col += i;
	p->pos += i;
}

void 			parse_expressions(t_asm_parser *p)
{
	if (p->f_data[p->pos] == '\n' && ++p->pos)
		push_lexeme(p, NL, NULL);
	else if (p->f_data[p->pos] == '.')
		get_command(p);
	else if (p->f_data[p->pos] == '"' && ++p->pos)
		get_string(p);
	else if (p->f_data[p->pos] == LABEL_CHAR || is_label_char(p->f_data[p->pos]))
		get_lirii(p);
	else if (p->f_data[p->pos] == DIRECT_CHAR && ++p->pos && ++p->col)
		get_direct(p);
	else if (p->f_data[p->pos] == SEPARATOR_CHAR && ++p->pos)
		push_lexeme(p, SEPARATOR, NULL);
	else
		lexical_error(p->row, p->col);
}