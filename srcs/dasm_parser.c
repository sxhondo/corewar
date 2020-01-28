#include "dasm.h"

static void		check_header(int fd)
{
	uint8_t		b[4];
	
	if ((read(fd, &b, 4)) != 4)
		display_error(INVALID_FILE);
	// ft_printf("[%#x] [%#x]\n", b[1], (COREWAR_EXEC_MAGIC) >> 16u);
	// ft_printf("[%#x] [%#x]\n", b[2], (uint8_t)(COREWAR_EXEC_MAGIC >> 8u));
	// ft_printf("[%#x] [%#x]\n", b[3], (uint8_t)(COREWAR_EXEC_MAGIC));
	if (b[0] == 0 &&
			b[1] == ((COREWAR_EXEC_MAGIC) >> 16u) &&
				b[2] == (uint8_t)(COREWAR_EXEC_MAGIC >> 8u) &&
					b[3] == (uint8_t)(COREWAR_EXEC_MAGIC))
					return ;
	else
		display_error(INVALID_HEADER);				
}

static char		*check_name(t_parser *p)
{
	int 		i, k;
	char		*res;
	uint8_t		b[PROG_NAME_LENGTH];
	
	if ((read(p->fd, &b, PROG_NAME_LENGTH) != PROG_NAME_LENGTH))
		display_error(INVALID_FILE);
	k = 0;	
	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		if (i != 0 && (i % 8) == 0)
			ft_printf("\n");
		ft_printf("%02x ", b[i]);
		if (b[i] != 0)
			k++;
		i++;
	}
	if ((res = (char*)malloc(sizeof(char) * k)) == NULL)
		display_error(CANT_ALLOCATE);
	i = -1;
	while (++i < k)
		res[i] = b[i];
	return (res);	
}

void			dasm_parser(char *path)
{
	uint8_t		b[4];
    t_parser	*p;

    p = init_parser(path);
	check_header(p->fd);
	p->name = check_name(p);

	ft_printf("\nname: %s\n", p->name);
	free(p->name);
    free(p);
    return ;
}