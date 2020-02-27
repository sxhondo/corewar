#include "vm.h"

void	parse_arguments(int ac, char **av, t_corewar *corewar)
{
	int		i;

	i = 0;
	while (++i < ac)
	{
		check_arg(av[i], corewar);
		if (corewar->flgs.flgs)
			write_flg_arg(av[++i], &corewar->flgs);
	}
}

void	check_arg(const char *arg, t_corewar *corewar)
{
	if (is_flg(arg, &corewar->flgs))
		return ;
	if (is_champion(arg, corewar->champs))
		return ;
	get_error();
}
