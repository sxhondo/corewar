#include "dasm.h"

static void		check_header(int fd)
{
	uint8_t		b[4];
	
	if ((read(fd, &b, 4)) != 4)
		display_error(INVALID_FILE);
	ft_printf("Header: [%x] [%x] [%x] [%x]\n\n", b[0], b[1], b[2], b[3]);
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
		if (i != 0 && (i % 8) == 0)
			ft_printf("\n");
		ft_printf("%02x ", b[i]);
		if (b[i] != 0)
			k++;
		i++;
	}
	if ((res = ft_strnew(k)) == NULL)
		display_error(CANT_ALLOCATE);
	ft_strncat(res, (char *)b, k);
	ft_printf("\n---\n");
	return (res);	
}

static void 		check_null(int fd)
{
	uint8_t			b[4];

	if ((read(fd, &b, 4) != 4))
		display_error(INVALID_FILE);
	if (b[0] || b[1] || b[2] || b[3])
		display_error(INVALID_NULL_1);

}

static unsigned 	check_exec_size(int fd)
{
	uint8_t			b[4];

	if ((read(fd, &b, 4) != 4))
		display_error(INVALID_FILE);
	return (b[0] + b[1] + b[2] + b[3]);
}

static uint8_t		get_arg_type(uint8_t code, unsigned bit)
{
	uint8_t			tmp;

	tmp = 0;
	tmp |= (code >> (bit - 1) & 1u) << 1;
	bit -= 1;
	tmp |= (code >> (bit - 1) & 1u) << 0;
	ft_printf("[%08b] - ", tmp);
	if (tmp == T_REG)
		ft_printf("[T_REG]");
	else if (tmp == T_DIR)
		ft_printf("[T_DIR]");
	else if (tmp == T_IND)
		ft_printf("[T_IND]");
	ft_printf("\n");
	return (tmp);
}

static void 		check_exec_code(int fd, int size, t_op *ops)
{
	int				i;
	uint8_t			b[size];
	t_op			tmp = {NULL, {0, 0, 0}};
	
	if ((read(fd, &b, size)) != size)
		display_error(INVALID_FILE);
	i = -1;
	while (++i < size)
	{
		if ((i % 8) == 0 && i != 0)
			ft_printf("\n");
		ft_printf("op: %#02x [%s]\n", b[i], op_tab[b[i] - 1].name);
		if (op_tab[b[i] - 1].args_type_code == 1)
		{
			ft_printf("args: %#02x\n", b[i + 1]);
			tmp.args[0] = get_arg_type(b[i + 1], 8);
			tmp.args[1] = get_arg_type(b[i + 1], 6);
			tmp.args[2] = get_arg_type(b[i + 1], 4);
			exit(0);
		}
	}	
	// exit(0);
	ft_printf("\n");
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
	check_exec_code(p->fd, p->exe_code_size, p->ops);
	ft_printf("\nname: %s\nex size: %d\ncomment: %s\n", p->name, p->exe_code_size, p->comment);

	free(p->comment);
	free(p->name);
    free(p);
    return ;
}