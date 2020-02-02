#include <dasm.h>

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
	t_int32			tmp;
	uint8_t			b[4];

	if ((read(fd, &b, 4) != 4))
		display_error(INVALID_FILE);
	tmp.octets.o1 = b[3];
	tmp.octets.o2 = b[2];
	tmp.octets.o3 = b[1];
	tmp.octets.o4 = b[0];
	return (tmp.num);
}

static uint8_t		get_arg_size(uint8_t arg_type_code, uint8_t op)
{
	if (arg_type_code == REG_CODE)
		return (1u);
	else if (arg_type_code == DIR_CODE)
		return (op_tab[op - 1].t_dir_size);
	else if (arg_type_code == IND_CODE)
		return (IND_SIZE);
	else
	{
		display_error(INVALID_ARG_SIZE);
		return (-1);
	}
}

static int32_t 		set_bits(const int8_t save[], int arg_size)
{
	t_int32			k;

	k.num = 0;
	if (arg_size == 4)
	{
		k.octets.o4 = save[0];
		k.octets.o3 = save[1];
		k.octets.o2 = save[2];
		k.octets.o1 = save[3];
	}
	if (arg_size == 3)
	{
		k.octets.o3 = save[0];
		k.octets.o2 = save[1];
		k.octets.o1 = save[2];
	}
	if (arg_size == 2)
	{
		k.octets.o2 = save[0];
		k.octets.o1 = save[1];
	}
	if (arg_size == 1)
		k.octets.o1 = save[0];
	return (k.num);
}

static int32_t 		get_dir_undir(const uint8_t code[], int pos, int arg_size)
{
	int 			i;
	int 			sign;
	uint32_t 		ret;
	int8_t 			save[arg_size];

	i = -1;
	sign = code[pos] & 0x80u ? 1 : 0;
	while (++i < arg_size)
		save[i] = sign ? ~(code[pos + i]) : code[pos + i];
	ret = set_bits(save, arg_size);
	return (sign ? -(ret + 1) : ret);
}

static uint8_t		get_reg(const uint8_t code[], int pos)
{
	uint8_t			ret;

	ret = code[pos];
	if (ret < 0x01 || ret > 0x10)
		display_error(REGISTER_OUT_OF_BOUNDS);
	return (ret);
}

static void			get_args_type(t_op *op, t_parser *p, const uint8_t code)
{
	int 				i;
	static t_int32		k = {0};

	if (op_tab[op->op - 1].args_type_code == 1)
	{
		k.num = code;
		op->args_type_code[0] = k.bin.b4;
		op->args_type_code[1] = k.bin.b3;
		op->args_type_code[2] = k.bin.b2;
		i = -1;
		while (++i < 3)
		{
			if (op->args_type_code[i] != 0
				&& op->args_type_code[i] != REG_CODE
					&& op->args_type_code[i] != DIR_CODE
						&& op->args_type_code[i] != IND_CODE)
				display_error(INVALID_TYPE_ARG);
		}
		p->pos += 1;
	}
	else
		op->args_type_code[0] = DIR_CODE;
}

static void 		get_arguments(t_parser *p, t_op *elem, uint8_t code[])
{
	int 			i;
	int 			arg_size;
	int 			arg_amount;

	arg_amount = op_tab[elem->op - 1].args_num;
//	ft_printf("\n\n[%s] args: (%d)\n", op_tab[elem->op - 1].name, arg_amount);
//	display_grid(code, p->exe_code_size, p->pos);
	i = -1;
	while (++i < arg_amount)
	{
		arg_size = get_arg_size(elem->args_type_code[i], elem->op);
		// ft_printf("size: %d byte\n", arg_size);
		if (elem->args_type_code[i] == REG_CODE)
			elem->args[i] = get_reg(code, p->pos);
		if (elem->args_type_code[i] == DIR_CODE)
			elem->args[i] = get_dir_undir(code, p->pos, arg_size);
		if (elem->args_type_code[i] == IND_CODE)
			elem->args[i] = get_dir_undir(code, p->pos, arg_size);
		p->pos += arg_size;
	}
}

static void 		check_exec_code(t_parser *p)
{
	uint8_t			b[p->exe_code_size];
	t_op			*elem;
	
	if ((read(p->fd, &b, p->exe_code_size)) != p->exe_code_size)
		display_error(INVALID_FILE);
	while (p->pos < p->exe_code_size)
	{
		elem = init_operation();
		elem->op = b[p->pos++];
		// ft_printf("(%s)\n", op_tab[elem->op - 1].name);
		if (elem->op < 0x01 || elem->op > 0x10)
			display_error(INVALID_OP_NAME);
		get_args_type(elem, p, b[p->pos]);
		get_arguments(p, elem, b);
		add_operation(&(p->ops), elem);
	}
}

void				dasm_parser(char *path)
{
    t_parser		*p;

    p = init_parser(path);
	check_header(p->fd);
	p->name = check_string(p->fd, PROG_NAME_LENGTH);
	check_null(p->fd);
	p->exe_code_size = check_exec_size(p->fd);
	p->comment = check_string(p->fd, COMMENT_LENGTH);
	check_null(p->fd);
	check_exec_code(p);
	display_collected(p);
	write_to_file(p, path);
	free_allocated(p);
}