#include "dasm.h"

static void		check_header(int fd)
{
	uint8_t		b[4];
	
	if ((read(fd, &b, 4)) != 4)
		display_error(INVALID_FILE);
	// ft_printf("Header: %x%x%x%x\n", b[0], b[1], b[2], b[3]);
	if (b[0] == 0u &&
			b[1] == ((COREWAR_EXEC_MAGIC) >> 16u) &&
				b[2] == (uint8_t)(COREWAR_EXEC_MAGIC >> 8u) &&
					b[3] == (uint8_t)(COREWAR_EXEC_MAGIC))
					return ;
	else
		display_error(INVALID_HEADER);				
}

static char		*check_string(int fd, int type)
{
	int 		i, k;
	char		*res;
	uint8_t		b[type];
	
	if ((read(fd, &b, type) != type))
		display_error(INVALID_FILE);
	k = 0;	
	i = 0;
	while (i < type)
	{
		// if (i != 0 && (i % 8) == 0)
		// 	ft_printf("\n");
		// ft_printf("%02x ", b[i]);
		if (b[i] != 0)
			k++;
		i++;
	}
	if ((res = ft_strnew(k)) == NULL)
		display_error(CANT_ALLOCATE);
	ft_strncat(res, (char *)b, k);
	// ft_printf("\n---\n");
	return (res);	
}

static void 		check_null(int fd)
{
	uint8_t			b[4];

	if ((read(fd, &b, 4) != 4))
		display_error(INVALID_FILE);
	if (b[0] || b[1] || b[2] || b[3])
		display_error(INVALID_NULL);

}

static unsigned 	check_exec_size(int fd)
{
	uint8_t			b[4];

	if ((read(fd, &b, 4) != 4))
		display_error(INVALID_FILE);
	return (b[0] + b[1] + b[2] + b[3]);
}

static uint8_t 		get_dir(t_parser *p, t_op *elem, uint8_t code[])
{
	int 			k;
	int 			tmp;
	int 			dir_size;

	k = -1;
	dir_size = op_tab[elem->op - 1].t_dir_size;
	while (++k < dir_size)
		tmp += code[p->pos];
	return (tmp);
}

static void 		get_arguments(t_parser *p, t_op *elem, uint8_t code[])
{
	int 			i, k;
	int 			t_dir_size;
	int 			arg_amount;

	arg_amount = op_tab[elem->op - 1].args_num;
	ft_printf("\n[%s] args: (%d)\n", 
	op_tab[elem->op - 1].name, arg_amount);
	
	i = -1;
	while (++i < arg_amount)
	{
		if (elem->args_type_code[i] == T_REG)
		{
			display_grid(code, p->exe_code_size, p->pos);
			elem->args[i] = code[p->pos];
			p->pos += T_REG;
		}
		if (elem->args_type_code[i] == T_DIR)
		{
			elem->args[i] = get_dir(p, elem, code);
			p->pos += op_tab[elem->op - 1].t_dir_size;
		}	
	}
	
}

static void			get_args_type(t_op *op, t_parser *p, uint8_t code)
{
	int 			i;
	unsigned		bit;
	
	if (op_tab[op->op - 1].args_type_code == 1)
	{
		i = 0;
		bit = 8;
		p->pos += 1;
		while (bit >= 3)
		{
			op->args_type_code[i] |= (code >> (bit - 1) & 1u) << 1;
			bit -= 1;
			op->args_type_code[i] |= (code >> (bit - 1) & 1u) << 0;
			bit -= 1;
			if (op->args_type_code[i] != T_REG 
					&& op->args_type_code[i] != T_DIR 
						&& op->args_type_code[i] != T_IND)
				display_error(INVALID_TYPE_ARG);
			++i;	
		}
	}	
	else
	{
		op->args_type_code[0] = T_DIR;
	}
}

static void 		check_exec_code(t_parser *p)
{
	uint8_t			b[p->exe_code_size];
	t_op			*elem;
	
	if ((read(p->fd, &b, p->exe_code_size)) != p->exe_code_size)
		display_error(INVALID_FILE);
	display_grid(b, p->exe_code_size, p->pos);
	elem = init_operation();
	while (p->pos < p->exe_code_size)
	{
		elem->op = b[p->pos++];
		if (elem->op < 0x01 || elem->op > 0x10)
			display_error(INVALID_OP_NAME);
		get_args_type(elem, p, b[p->pos]);
		get_arguments(p, elem, b);
		add_operation(&(p->ops), elem);
		elem = init_operation();
	}
}

void				dasm_parser(char *path)
{
	uint8_t			b[4];
    t_parser		*p;

    p = init_parser(path);
	check_header(p->fd);
	p->name = check_string(p->fd, PROG_NAME_LENGTH);
	check_null(p->fd);
	p->exe_code_size = check_exec_size(p->fd);
	p->comment = check_string(p->fd, COMMENT_LENGTH);
	check_null(p->fd);
	// ft_printf("\nname: %s\nex size: %d\ncomment: %s\n", p->name, p->exe_code_size, p->comment);
	check_exec_code(p);

	free(p->comment);
	free(p->name);
    free(p);
    return ;
}