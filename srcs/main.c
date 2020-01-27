#include "d_asm.h"

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
        d_asm_parser(av[1]);
    }
    else
        display_error(INVALID_FILE);
    return (0);
}
