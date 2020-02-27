#include "vm.h"

int		main(int ac, char **av)
{
	t_corewar	corewar;

	if (ac == 1)
		get_usage();
	init_struct(&corewar);
	parse_arguments(ac, av, &corewar);
	return (0);
}
