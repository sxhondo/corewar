#include "asm.h"

char 		*new_ext(char *path)
{
	int 	i;
	char 	*new;

	i = 0;
	while (path[i] && path[i] != '.')
		i++;
	if (!(new = ft_strnew(i + 4)))
		common_error(CANT_ALLOCATE);
	ft_strncat(new, path, i);
	ft_strncat(new, ".cor", 4);
	return (new);


}

void 		write_in_file(t_vec *code, char *path)
{
	int 	fd;
	char 	*ext;
	char 	*c;

	ext = new_ext(path);
	if ((fd = open(ext, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO)) < 0)
		common_error(CANT_CREATE);
	ft_printf("Writing output to ... %s\n", ext);
	c = code->data;
	write(fd, c, code->total);
	ft_strdel(&ext);
	ft_vec_del(&code);
}