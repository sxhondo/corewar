#include "asm.h"

static void 		get_string(t_asm_parser *p)
{
	char 			*new;
	int 			i;

	i = 0;
	while (p->f_data[p->pos + i] != '"')
		i++;
	if (!(new = ft_strndup(p->f_data + p->pos, i)))
		common_error(CANT_ALLOCATE);
	push_lexeme(p, STRING, new);
	p->pos += i + 1;
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
	push_lexeme(p, INSTRUCTION, tmp);
	p->col += i;
	p->pos += i;
}

static char 		*get_direct(t_asm_parser *p)
{
	int 			i;
	char 			*tmp;

	i = 0;
	if (p->f_data[p->pos] == ':' && p->pos++ && p->col++)
	{
		while (p->f_data[p->pos + i] && is_label_char(p->f_data[p->pos + i]))
			i++;
	}
	else if (is_num(p->f_data[p->pos]))
	{
		while (p->f_data[p->pos + i] && is_num(p->f_data[p->pos + i]))
			i++;
	}
	if (!(tmp = ft_strndup(p->f_data + p->pos, i)))
		common_error(CANT_ALLOCATE);
	push_lexeme(p, DIRECT, tmp);
	p->pos += i;
	p->col += i;
	return (tmp);
}

static char 		*get_liri(t_asm_parser *p)
{
	char 			*tmp;
	int 			i;

	i = 0;
	while (p->f_data[p->pos + i] &&
		   (is_label_char(p->f_data[p->pos + i]) ||
			p->f_data[p->pos + i] == LABEL_CHAR))
		i++;
	if (!(tmp = ft_strndup(p->f_data + p->pos, i)))
		common_error(CANT_ALLOCATE);
	else
	{
		if (tmp[ft_strlen(tmp) - 1] == LABEL_CHAR)
			push_lexeme(p, LABEL, tmp);
		else if (is_valid_instruction(tmp))
			push_lexeme(p, INSTRUCTION, tmp);
		else if (tmp[0] == 'r')
			push_lexeme(p, REGISTER, tmp);
		else
			push_lexeme(p, INDIRECT, tmp);
	}
	p->col += i;
	p->pos += i;
	return (tmp);
}

void 			parse_expressions(t_asm_parser *p)
{
	if (p->f_data[p->pos] == '\n' && ++p->pos)
		push_lexeme(p, NL, NULL);
	else if (p->f_data[p->pos] == '.')
		get_command(p);
	else if (p->f_data[p->pos] == '"' && ++p->pos)
		get_string(p);
	else if (is_label_char(p->f_data[p->pos]))
		get_liri(p);
	else if (p->f_data[p->pos] == DIRECT_CHAR && ++p->pos && ++p->col)
		get_direct(p);
	else if (p->f_data[p->pos] == SEPARATOR_CHAR && ++p->pos)
		push_lexeme(p, SEPARATOR, NULL);
	else
		lexical_error(p->row, p->col);
}
