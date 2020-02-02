#include "dasm.h"

static char 	*update_path(char *path)
{
	int 		len;
	char 		*str;

	len = ft_strlen(path);
	if ((str = ft_strnew(len - 2)) == NULL)
		display_error(CANT_ALLOCATE);
	ft_strncat(str, "test.", len - 3);
	ft_strcat(str, "s");
	return (str);
}

static void 	write_operations(t_parser *p, int fd)
{
	int 		i;
	t_op 		*op;
	
	op = p->ops;
	while (op)
	{
		ft_fprintf(fd, "%s ", op_tab[op->op - 1].name);
		if (op_tab[op->op - 1].args_type_code == 0)
			ft_fprintf(fd, "%c%d", DIRECT_CHAR, op->args[0]);
		else
		{
			i = 0;
			while (i < op_tab[op->op - 1].args_num)
			{
				if (op->args_type_code[i] == DIR_CODE)
					ft_fprintf(fd, "%c%d", DIRECT_CHAR, op->args[i]);
				if (op->args_type_code[i] == REG_CODE)
					ft_fprintf(fd, "%c%d", 'r', op->args[i]);
				if (op->args_type_code[i] == IND_CODE)
					ft_fprintf(fd, "%d", op->args[i]);
				if (i + 1 < op_tab[op->op - 1].args_num)
					ft_fprintf(fd, ", ");
				i++;
			}
		}	
		ft_fprintf(fd, "\n");
		op = op->next;
	}
}

void 			write_to_file(t_parser *p, char *path)
{
	int 		fd;
	char 		*up;
	t_op 		*op;

	up = update_path(path);
	if ((fd = open(up, O_CREAT | O_WRONLY | O_TRUNC,
				   S_IRWXU | S_IRWXG | S_IRWXO)) < 0)
		display_error(CANT_CREATE);
	ft_fprintf(fd, ".name \"%s\"\n", p->name);
	ft_fprintf(fd, ".comment \"%s\"\n\n", p->comment);
	write_operations(p, fd);
	close(fd);
	ft_strdel(&up);
	
}