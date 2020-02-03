#include "asm.h"

static t_vec    	*vec_read(int fd)
{
	t_vec			*vec;
	char			buf[1];

	if (!(vec = ft_vec_init(1, sizeof(char))))
		asm_error(CANT_ALLOCATE, 0, 0);
	while (read(fd, buf, sizeof(buf)) > 0)
	{
		// ? ? ? //
//		if (vec->total >= CHAMP_MAX_SIZE)
//		{
//			ft_vec_del(&vec);
//			display_error(FILE_TOO_BIG, 0, 0);
//		}
		// ? ? ? //
		ft_vec_add(&vec, buf);
	}
	ft_vec_add(&vec, "\0");
	if (!(ft_vec_resize(&vec)))
	{
		ft_vec_del(&vec);
		asm_error(CANT_ALLOCATE, 0, 0);
	}
	return (vec);
}

t_asm_parser         *init_asm_parser(char *path)
{
	t_asm_parser	*p;

	if ((p = ft_memalloc(sizeof(t_asm_parser))) == NULL)
		asm_error(CANT_ALLOCATE, 0, 0);
	if ((p->fd = open(path, O_RDONLY)) < 0)
		asm_error(CANT_OPEN, 0, 0);
	p->file = vec_read(p->fd);
	p->row = 1;
	p->col = 1;
	p->f_data = p->file->data;
	p->pos = 0;
	return (p);
}