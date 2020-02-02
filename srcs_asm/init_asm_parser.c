#include "asm.h"

static t_vec    	*vec_read(int fd)
{
	t_vec			*vec;
	char			buf[1];

	if (!(vec = ft_vec_init(1, sizeof(char))))
		display_error(CANT_ALLOCATE);
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
		display_error(CANT_ALLOCATE);
	}
	return (vec);
}

t_asm_parser         *init_parser(char *path)
{
	t_asm_parser	*p;

	if ((p = ft_memalloc(sizeof(t_asm_parser))) == NULL)
		display_error(CANT_ALLOCATE);
	if ((p->fd = open(path, O_RDONLY)) < 0)
		display_error(CANT_OPEN);
	p->file = vec_read(p->fd);
	p->lc_total = 0u;
	return (p);
}