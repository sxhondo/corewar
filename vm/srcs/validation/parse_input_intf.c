#include "vm.h"

_Bool	is_flg(const char *arg, t_flgs *flgs)
{
	_Bool	good;

	good = 1;
	if (!ft_strcmp(arg, "-n"))
		flgs->flgs |= N_FLG;
	else if (!ft_strcmp(arg, "-dump"))
		flgs->flgs |= DUMP_FLG;
	else if (!ft_strcmp(arg, "-a"))
		flgs->flgs |= A_FLG;
	else
		good = 0;
	return (good);
}

_Bool is_champion(const char *arg, t_champion *champs)
{
	char	*lst_dot;

	lst_dot = ft_strrchr(arg, '.');
	if (!lst_dot || ft_strcmp(lst_dot + 1, "cor"))
		return (0);
	push_back_champ(champs, arg);
	return (1);
}

void	write_flg_arg(const char *arg, t_flgs *flgs)
{
	if (flgs->flgs & N_FLG)
		flgs->nxt_player_num = ft_atoi(arg);
	else if (flgs->flgs & DUMP_FLG)
		flgs->nbr_cycles_dump = ft_atoi(arg);
}
