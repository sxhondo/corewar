#include "asm.h"
#include "dasm.h"

static int		check_ext(char *path)
{
	while (*path)
	{
		if (*path == '.' && ft_strequ(path, ".s"))
			return (1);
		if (*path == '.' && ft_strequ(path, ".cor"))
			return (2);
		path++;
	}
	return (0);
}


int				main(int ac, char **av)
{
	if (ac == 2 && check_ext(av[1]))
	{
		if (check_ext(av[1]) == 1)
			asm_parser(av[1]);
		else if (check_ext(av[1]) == 2)
			dasm_parser(av[1]);
	}
	else
		common_error(BAD_ARGUMENT_FILE);
	return (0);
}