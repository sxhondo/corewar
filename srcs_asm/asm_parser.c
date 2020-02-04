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

static int 			is_label_char(char ch)
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
	unsigned		sr;

	dst = NULL;
	sr = p->row;
	while (skip_empty_space(p))
	{
		i = 0;
		if (sr == p->row)
			asm_error(NO_NEW_LINE_LABEL, p->row, p->col);
		while (p->f_data[p->pos + i] && is_label_char(p->f_data[p->pos + i]))
			i++;
		if (p->f_data[p->pos + i] == '\0')
			asm_error(EOF, p->row, p->col + i);
		else if (p->f_data[p->pos + i] == LABEL_CHAR)
			add_label(&dst, init_label(p->f_data + p->pos, i, p));
		else
			break ;
		sr = p->row;
		p->pos += i + 1;
		skip_tab_space(p);
	}
	return (dst);
}

static int			check_instruction(char *ins, t_asm_parser *p, int len)
{
	int 			i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(ins, op_tab[i].name))
		{
			p->pos += len;
			return (op_tab[i].code);
		}
		i++;
	}
	asm_error(BAD_INSTRUCTION, p->row, p->col);
	return (-1);
}

int32_t 			*args_parser(t_asm_parser *p, int icode)
{
	int 			arg[3];
	char 			type;
	int 			a;

	a = 0;
	skip_tab_space(p);
	while (p->f_data[p->pos] && p->f_data[p->pos] != '\n')
	{
		if (p->f_data[p->pos++] == '%')
		{
			if (!(op_tab[icode - 1].args_types[a] & T_DIR))
				asm_error(WRONG_ARGUMENT, p->row, p->col);
			core_atoi(p->f_data + p->pos, &arg[a], p);
			ft_printf("%d", arg[a]);
			exit(0);
		}
	}
	ft_printf("%s", p->f_data + p->pos);
	exit(0);
}

t_ins 				*ins_parser(t_asm_parser *p, t_label *lab)
{
	int 			i;
	char 			*ins;
	int 			icode;
	int 			*args;

	i = 0;
	while (p->f_data[p->pos + i] && ft_isalpha(p->f_data[p->pos + i]))
		i++;
	if ((ins = ft_strndup(p->f_data + p->pos, i)) == NULL)
		asm_error(CANT_ALLOCATE, 0, 0);
	icode = check_instruction(ins, p, i);
	args = args_parser(p, icode);

	ft_printf("%s", ins);


//	ft_printf("%d : %d\n", p->row, p->col);
//	ft_printf("%s", p->f_data + p->pos);
	exit(0);
}

void				asm_parser(char *path)
{
	t_label			*lab;
    t_asm_parser	*p;

    p = init_asm_parser(path);
	get_comment_name(p);
	while (1)
	{
		lab = label_parser(p);
		print_label(lab);
		ins_parser(p, lab);
		break ;
	}
	exit(0);


    ft_strdel(&(p->name));
    ft_strdel(&(p->comment));
    ft_vec_del(&(p->file));
    free(p);
}