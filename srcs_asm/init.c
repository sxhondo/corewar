#include "asm.h"

static t_vec    	*vec_read(int fd)
{
	t_vec			*vec;
	char			buf[1];

	if (!(vec = ft_vec_init(1, sizeof(char))))
		common_error(CANT_ALLOCATE);
	while (read(fd, buf, sizeof(buf)) > 0)
		ft_vec_add(&vec, buf);
	ft_vec_add(&vec, "\0");
	if (!(ft_vec_resize(&vec)))
	{
		ft_vec_del(&vec);
		common_error(CANT_ALLOCATE);
	}
	return (vec);
}

t_asm_parser			*init_asm_parser(char *path)
{
	t_asm_parser		*p;

	if ((p = ft_memalloc(sizeof(t_asm_parser))) == NULL)
		common_error(CANT_ALLOCATE);
	if ((p->fd = open(path, O_RDONLY)) < 0)
		common_error(CANT_OPEN);
	p->file = vec_read(p->fd);
	p->f_data = p->file->data;
	if (!(p->code = ft_vec_init(1, sizeof(uint8_t))))
		common_error(CANT_ALLOCATE);
	p->row = 0;
	p->col = 0;
	p->pos = 0;
	return (p);
}