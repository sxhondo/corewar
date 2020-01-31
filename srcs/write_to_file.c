#include "dasm.h"

static char 	*update_path(char *path)
{
	int 		len;
	char 		*str;

	len = ft_strlen(path);
	if ((str = ft_strnew(len - 2)) == NULL)
		display_error(CANT_ALLOCATE);
	ft_strncat(str, path, len - 3);
	ft_strcat(str, "s");
	return (str);

}

void 			write_to_file(t_parser *p, char *path)
{
	int 		fd;
	char 		*up;
	t_op 		*tmp;

	display_collected(p);
	up = update_path(path);
	if ((fd = open(up, O_CREAT | O_WRONLY | O_TRUNC, 777)) < 0)
		display_error(CANT_CREATE);
	ft_fprintf(fd, ".name %s\n", p->name);
	ft_fprintf(fd, ".comment %s\n", p->comment);
		
	close(fd);
	ft_strdel(&up);
	
}