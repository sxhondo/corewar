#include "dasm.h"

static int		check_ext(char *path)
{
    while (*path)
    {
        if (*path == '.' && ft_strequ(path, ".cor"))
            return (1);
        path++;
    }
    return (0);
}

int				main(int ac, char **av)
{
    if (ac == 2 && check_ext(av[1]))
    {
        dasm_parser(av[1]);
    }
    else
        d_error(INVALID_FILE);
    return (0);
}
